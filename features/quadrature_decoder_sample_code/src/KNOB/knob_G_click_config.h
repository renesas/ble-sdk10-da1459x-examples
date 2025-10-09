/**
 ****************************************************************************************
 *
 * @file knob_G_click_config.h
 *
 * @brief Quadrature decoder default configuration values. Values can be overwritten by re-definig
 *        the corresponding macro into the customer configuration file i.e. custom_config_xxx.h.
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

#ifndef KNOB_G_CLICK_CONFIG_H_
#define KNOB_G_CLICK_CONFIG_H_

#ifndef KNOB_G_CLICK_SDA_PORT
#define KNOB_G_CLICK_SDA_PORT  ( HW_GPIO_PORT_0 )
#endif

#ifndef KNOB_G_CLICK_SDA_PIN
#define KNOB_G_CLICK_SDA_PIN   ( HW_GPIO_PIN_0 )
#endif

#ifndef KNOB_G_CLICK_SCL_PORT
#define KNOB_G_CLICK_SCL_PORT  ( HW_GPIO_PORT_0 )
#endif

#ifndef KNOB_G_CLICK_SCL_PIN
#define KNOB_G_CLICK_SCL_PIN   ( HW_GPIO_PIN_1 )
#endif

#ifndef KNOB_G_CLICK_RST_PORT
#define KNOB_G_CLICK_RST_PORT  ( HW_GPIO_PORT_0 )
#endif

#ifndef KNOB_G_CLICK_RST_PIN
#define KNOB_G_CLICK_RST_PIN   ( HW_GPIO_PIN_2 )
#endif

#ifndef KNOB_G_CLICK_I2C_ADDR
#define KNOB_G_CLICK_I2C_ADDR   ( 0x70 )
#endif

#ifndef KNOB_G_CLICK_KEY_PORT
#define KNOB_G_CLICK_KEY_PORT   ( HW_GPIO_PORT_0 )
#endif

#ifndef KNOB_G_CLICK_KEY_PIN
#define KNOB_G_CLICK_KEY_PIN    ( HW_GPIO_PIN_3 )
#endif

/*
 * KNOB G Click should connect its SW signal to logic high
 * and thus, KEY press events occur when the SW signal is
 * grounded. The triggering edge should be used to properly
 * configure the WKUP controller.
 */
#ifndef KNOB_G_CLICK_KEY_ACTIVE_LOW
#define KNOB_G_CLICK_KEY_ACTIVE_LOW  ( 1 )
#endif

/* Configuration pre-processor to include/exclude KNOB KEY support. */
#ifndef KNOB_G_CLICK_KEY_ENABLE
#define KNOB_G_CLICK_KEY_ENABLE      ( 1 )
#endif

/* Configuration pre-processor to include/exclude KNOB LED support. */
#ifndef KNOB_G_CLICK_LED_ENABLE
#define KNOB_G_CLICK_LED_ENABLE      ( 1 )
#endif

#endif /* KNOB_G_CLICK_CONFIG_H_ */
