#include "esp_log.h"
#include "screen_driver.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "JD7601 3.7\" E6 %dx%d", SCREEN_WIDTH, SCREEN_HEIGHT);

    ESP_ERROR_CHECK(screen_driver_init());

    /* 与厂商 main 一致：先铺满绿色 */
    ESP_LOGI(TAG, "fill GREEN …");
    ESP_ERROR_CHECK(screen_driver_fill(SCREEN_COLOR_GREEN));

    /* 再画六色条，确认 6 色都能出 */
    ESP_LOGI(TAG, "show color bars …");
    ESP_ERROR_CHECK(screen_driver_show_bars());

    ESP_ERROR_CHECK(screen_driver_deep_sleep());
    ESP_LOGI(TAG, "done");
}
