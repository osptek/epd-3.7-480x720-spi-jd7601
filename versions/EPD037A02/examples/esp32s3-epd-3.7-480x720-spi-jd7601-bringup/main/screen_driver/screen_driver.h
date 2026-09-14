#ifndef SCREEN_DRIVER_H
#define SCREEN_DRIVER_H

#include "esp_err.h"
#include <stddef.h>
#include <stdint.h>

/* 3.7" E6 480x720 JD7601；每像素 4bit，厂商按列发送 720 x 240 字节 */
#define SCREEN_WIDTH       480
#define SCREEN_HEIGHT      720
#define SCREEN_FRAME_BYTES (SCREEN_WIDTH * SCREEN_HEIGHT / 2)

/* 与厂商 3D7_E6_480x720_7601.c 色值一致 */
typedef enum {
    SCREEN_COLOR_BLACK  = 0x0,
    SCREEN_COLOR_WHITE  = 0x1,
    SCREEN_COLOR_YELLOW = 0x2,
    SCREEN_COLOR_RED    = 0x3,
    SCREEN_COLOR_BLUE   = 0x5,
    SCREEN_COLOR_GREEN  = 0x6,
} screen_color_t;

esp_err_t screen_driver_init(void);
esp_err_t screen_driver_fill(screen_color_t color);
/* 沿 720 方向画六色条：黑 / 白 / 黄 / 红 / 蓝 / 绿 */
esp_err_t screen_driver_show_bars(void);
esp_err_t screen_driver_deep_sleep(void);

#endif /* SCREEN_DRIVER_H */
