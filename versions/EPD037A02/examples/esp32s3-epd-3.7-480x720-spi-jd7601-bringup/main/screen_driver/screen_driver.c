/*
 * JD7601 3.7" E6 480x720
 * 命令时序移植自厂商 3D7_E6_480x720_7601.c（MSP430 位带 SPI）
 * 引脚：pin_map.h
 */

#include "screen_driver.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "pin_map.h"

static const char *TAG = "screen";

#define EINK_SPI_HOST         SPI2_HOST
#define EINK_SPI_CLOCK_HZ     (2 * 1000 * 1000)
#define EINK_CHUNK_BYTES      4096
#define EINK_BUSY_TIMEOUT_MS  60000
#define EINK_COL_BYTES        (SCREEN_WIDTH / 2) /* 240 */

typedef struct {
    spi_device_handle_t spi;
    SemaphoreHandle_t lock;
    bool inited;
} screen_ctx_t;

static screen_ctx_t s_ctx;

static void delay_ms(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

/* 厂商 READBUSY：BUSY=1 表示空闲 */
static esp_err_t wait_busy(void)
{
    const TickType_t deadline = xTaskGetTickCount() + pdMS_TO_TICKS(EINK_BUSY_TIMEOUT_MS);
    while (gpio_get_level(eink_busy) == 0) {
        if (xTaskGetTickCount() > deadline) {
            ESP_LOGE(TAG, "BUSY timeout");
            return ESP_ERR_TIMEOUT;
        }
        vTaskDelay(1);
    }
    return ESP_OK;
}

static void lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
    int dc = (int)t->user;
    gpio_set_level(eink_dc, dc);
}

static esp_err_t write_cmd(uint8_t cmd)
{
    spi_transaction_t t = {
        .length = 8,
        .tx_buffer = &cmd,
        .user = (void *)0,
    };
    return spi_device_polling_transmit(s_ctx.spi, &t);
}

static esp_err_t write_data(const uint8_t *data, size_t len)
{
    while (len > 0) {
        size_t chunk = len > EINK_CHUNK_BYTES ? EINK_CHUNK_BYTES : len;
        spi_transaction_t t = {
            .length = chunk * 8,
            .tx_buffer = data,
            .user = (void *)1,
        };
        esp_err_t err = spi_device_polling_transmit(s_ctx.spi, &t);
        if (err != ESP_OK) {
            return err;
        }
        data += chunk;
        len -= chunk;
    }
    return ESP_OK;
}

static esp_err_t write_data_byte(uint8_t data)
{
    return write_data(&data, 1);
}

static esp_err_t write_solid(uint8_t pixel_byte, size_t count)
{
    uint8_t *chunk = heap_caps_malloc(EINK_CHUNK_BYTES, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
    if (chunk == NULL) {
        chunk = malloc(EINK_CHUNK_BYTES);
    }
    if (chunk == NULL) {
        return ESP_ERR_NO_MEM;
    }
    memset(chunk, pixel_byte, EINK_CHUNK_BYTES);

    esp_err_t err = ESP_OK;
    while (count > 0) {
        size_t n = count > EINK_CHUNK_BYTES ? EINK_CHUNK_BYTES : count;
        err = write_data(chunk, n);
        if (err != ESP_OK) {
            break;
        }
        count -= n;
    }
    free(chunk);
    return err;
}

/* 厂商 RESET：RST 拉低/拉高各两次后再等 BUSY */
static esp_err_t hw_reset(void)
{
    gpio_set_level(eink_rst, 0);
    delay_ms(20);
    gpio_set_level(eink_rst, 1);
    delay_ms(10);
    gpio_set_level(eink_rst, 0);
    delay_ms(20);
    gpio_set_level(eink_rst, 1);
    delay_ms(10);
    ESP_RETURN_ON_ERROR(wait_busy(), TAG, "reset busy");
    delay_ms(10);
    return ESP_OK;
}

/* 厂商 INIT_JD7601 */
static esp_err_t init_jd7601(void)
{
    ESP_RETURN_ON_ERROR(write_cmd(0xE9), TAG, "cmd E9");
    ESP_RETURN_ON_ERROR(write_data_byte(0x01), TAG, "data E9");
    return ESP_OK;
}

/* 厂商 0x04 / 0x12 / 0x02 */
static esp_err_t panel_refresh(void)
{
    ESP_RETURN_ON_ERROR(write_cmd(0x04), TAG, "PON");
    ESP_RETURN_ON_ERROR(wait_busy(), TAG, "PON busy");
    delay_ms(10);

    ESP_RETURN_ON_ERROR(write_cmd(0x12), TAG, "DRF");
    ESP_RETURN_ON_ERROR(write_data_byte(0x00), TAG, "DRF data");
    delay_ms(10);
    ESP_RETURN_ON_ERROR(wait_busy(), TAG, "DRF busy");

    ESP_RETURN_ON_ERROR(write_cmd(0x02), TAG, "POF");
    ESP_RETURN_ON_ERROR(write_data_byte(0x00), TAG, "POF data");
    ESP_RETURN_ON_ERROR(wait_busy(), TAG, "POF busy");
    delay_ms(20);
    return ESP_OK;
}

static uint8_t color_byte(screen_color_t color)
{
    return (uint8_t)((color << 4) | color);
}

esp_err_t screen_driver_init(void)
{
    if (s_ctx.inited) {
        return ESP_OK;
    }

    s_ctx.lock = xSemaphoreCreateMutex();
    if (s_ctx.lock == NULL) {
        return ESP_ERR_NO_MEM;
    }

    gpio_config_t io_out = {
        .pin_bit_mask = (1ULL << eink_dc) | (1ULL << eink_rst),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&io_out), TAG, "gpio out");

    gpio_config_t io_in = {
        .pin_bit_mask = (1ULL << eink_busy),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&io_in), TAG, "gpio busy");

    gpio_set_level(eink_rst, 1);
    gpio_set_level(eink_dc, 1);

    spi_bus_config_t buscfg = {
        .mosi_io_num = eink_sda,
        .miso_io_num = -1,
        .sclk_io_num = eink_clk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = EINK_CHUNK_BYTES,
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(EINK_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO),
                        TAG, "spi bus");

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = EINK_SPI_CLOCK_HZ,
        .mode = 0,
        .spics_io_num = eink_cs,
        .queue_size = 4,
        .pre_cb = lcd_spi_pre_transfer_callback,
        .flags = SPI_DEVICE_NO_DUMMY,
    };
    ESP_RETURN_ON_ERROR(spi_bus_add_device(EINK_SPI_HOST, &devcfg, &s_ctx.spi),
                        TAG, "spi device");

    ESP_LOGI(TAG, "pins SDA=%d CLK=%d CS=%d DC=%d RST=%d BUSY=%d",
             (int)eink_sda, (int)eink_clk, (int)eink_cs,
             (int)eink_dc, (int)eink_rst, (int)eink_busy);

    ESP_RETURN_ON_ERROR(hw_reset(), TAG, "reset");
    ESP_RETURN_ON_ERROR(wait_busy(), TAG, "busy");
    ESP_RETURN_ON_ERROR(init_jd7601(), TAG, "init");

    s_ctx.inited = true;
    ESP_LOGI(TAG, "JD7601 ready %dx%d", SCREEN_WIDTH, SCREEN_HEIGHT);
    return ESP_OK;
}

esp_err_t screen_driver_fill(screen_color_t color)
{
    if (!s_ctx.inited) {
        return ESP_ERR_INVALID_STATE;
    }

    xSemaphoreTake(s_ctx.lock, portMAX_DELAY);

    esp_err_t err = write_cmd(0x10);
    if (err == ESP_OK) {
        err = wait_busy();
    }
    if (err == ESP_OK) {
        err = write_solid(color_byte(color), SCREEN_FRAME_BYTES);
    }
    if (err == ESP_OK) {
        err = panel_refresh();
    }

    xSemaphoreGive(s_ctx.lock);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "fill color=0x%X done", (unsigned)color);
    }
    return err;
}

esp_err_t screen_driver_show_bars(void)
{
    static const screen_color_t bars[] = {
        SCREEN_COLOR_BLACK,
        SCREEN_COLOR_WHITE,
        SCREEN_COLOR_YELLOW,
        SCREEN_COLOR_RED,
        SCREEN_COLOR_BLUE,
        SCREEN_COLOR_GREEN,
    };
    const size_t bar_count = sizeof(bars) / sizeof(bars[0]);
    const size_t cols_per_bar = SCREEN_HEIGHT / bar_count;
    const size_t bytes_per_bar = cols_per_bar * EINK_COL_BYTES;

    if (!s_ctx.inited) {
        return ESP_ERR_INVALID_STATE;
    }

    xSemaphoreTake(s_ctx.lock, portMAX_DELAY);

    esp_err_t err = write_cmd(0x10);
    if (err == ESP_OK) {
        err = wait_busy();
    }
    for (size_t i = 0; err == ESP_OK && i < bar_count; i++) {
        err = write_solid(color_byte(bars[i]), bytes_per_bar);
    }
    if (err == ESP_OK) {
        err = panel_refresh();
    }

    xSemaphoreGive(s_ctx.lock);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "color bars done");
    }
    return err;
}

esp_err_t screen_driver_deep_sleep(void)
{
    if (!s_ctx.inited) {
        return ESP_ERR_INVALID_STATE;
    }

    xSemaphoreTake(s_ctx.lock, portMAX_DELAY);
    esp_err_t err = write_cmd(0x07);
    if (err == ESP_OK) {
        err = write_data_byte(0xA5);
    }
    xSemaphoreGive(s_ctx.lock);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "deep sleep");
    }
    return err;
}
