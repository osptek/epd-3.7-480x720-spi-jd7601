#ifndef PIN_MAP_H
#define PIN_MAP_H

#include "driver/gpio.h"

/* screen — 3.7" E6 480x720 JD7601 */
#define eink_sda    GPIO_NUM_15
#define eink_clk    GPIO_NUM_16
#define eink_cs     GPIO_NUM_12
#define eink_dc     GPIO_NUM_13
#define eink_rst    GPIO_NUM_14
#define eink_busy   GPIO_NUM_11

#endif /* PIN_MAP_H */
