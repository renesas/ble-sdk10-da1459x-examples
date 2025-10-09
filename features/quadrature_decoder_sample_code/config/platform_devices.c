/**
 ****************************************************************************************
 *
 * @file platform_device.c
 *
 * @brief Platform devices source file. This is the recommended place to define peripheral drivers.
 *
 * Copyright (C) 2015-2024 Renesas Electronics Corporation and/or its affiliates
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
# OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************************
 */

#include "ad_i2c.h"
#include "platform_devices.h"
#include "knob_G_click_config.h"

/*
 * PLATFORM PERIPHERALS GPIO CONFIGURATION
 *****************************************************************************************
 */

#if KNOB_G_CLICK_LED_ENABLE

/* I2C I/O configuration */
static const ad_i2c_io_conf_t pca9956b_led_io = {
        .scl = {
                .port = KNOB_G_CLICK_SCL_PORT, .pin = KNOB_G_CLICK_SCL_PIN,
                .on =  { HW_GPIO_MODE_OUTPUT_OPEN_DRAIN, HW_GPIO_FUNC_I2C_SCL, false },
                .off = { HW_GPIO_MODE_INPUT,            HW_GPIO_FUNC_GPIO,    true  }
        },
        .sda = {
                .port = KNOB_G_CLICK_SDA_PORT, .pin = KNOB_G_CLICK_SDA_PIN,
                .on =  { HW_GPIO_MODE_OUTPUT_OPEN_DRAIN, HW_GPIO_FUNC_I2C_SDA, false },
                .off = { HW_GPIO_MODE_INPUT,            HW_GPIO_FUNC_GPIO,    true  }
        },
};


/*
 * PLATFORM PERIPHERALS CONTROLLER CONFIGURATION
 *****************************************************************************************
 */

static const ad_i2c_driver_conf_t pca9956b_led_drv = {
                I2C_DEFAULT_CLK_CFG,
                .i2c.speed = HW_I2C_SPEED_FAST,
                .i2c.mode = HW_I2C_MODE_MASTER,
                .i2c.addr_mode = HW_I2C_ADDRESSING_7B,
                .i2c.address = KNOB_G_CLICK_I2C_ADDR,
#if (HW_I2C_DMA_SUPPORT == 1)
                .dma_channel = HW_DMA_CHANNEL_0
#endif
};


/* I2C controller configuration */
const ad_i2c_controller_conf_t pca9956b_led_cfg = {
        .id = HW_I2C1,
        .io = &pca9956b_led_io,
        .drv = &pca9956b_led_drv
};

#endif /* dg_configI2C_ADAPTER */

