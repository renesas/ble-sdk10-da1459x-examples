/**
 ****************************************************************************************
 *
 * @file knob_G_click_led.c
 *
 * @brief Source file to support the PCA9956B LED driver of KNOB G CLICK.
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

#include "misc.h"
#include "osal.h"
#include "knob_G_click_led.h"
#include "knob_G_click_config.h"

#if (KNOB_G_CLICK_LED_ENABLE == 1)

#define KNOB_REG_BRIGHTNESS_CONTROL_FOR_ALL_LED   0x3F
#define KNOB_REG_GAIN_CONTROL_FOR_ALL_LED         0x40

static int knob_G_click_led_write_reg(knob_G_click_led_cfg_t *ctx, uint8_t reg, const uint8_t *wbuf, size_t len)
{
        int ret;

        ret = ctx->write(ctx->handle, reg, wbuf, len);

        return ret;
}

#if ( 0 )
static int knob_G_click_led_read_reg(knob_G_click_led_cfg_t *ctx, uint8_t reg, uint8_t *rbuf, size_t len)
{
        int ret;

        ret = ctx->read(ctx->handle, reg, rbuf, len);

        return ret;
}
#endif

void knob_G_click_led_turn_on(knob_G_click_led_cfg_t *ctx, KNOB_G_CLICK_LED led)
{
        ASSERT_WARNING(led <= KNOB_G_CLICK_LED_MAX);

        uint8_t value = KNOB_G_CLICK_LED_ON;

        knob_G_click_led_write_reg(ctx, 0x09 + led, &value, 1);
}

void knob_G_click_led_turn_off(knob_G_click_led_cfg_t *ctx, KNOB_G_CLICK_LED led)
{
        ASSERT_WARNING(led <= KNOB_G_CLICK_LED_MAX);

        uint8_t value = KNOB_G_CLICK_LED_OFF;

        knob_G_click_led_write_reg(ctx, 0x09 + led, &value, 1);
}

void knob_G_click_led_set_brightness(knob_G_click_led_cfg_t *ctx, KNOB_G_CLICK_LED led, uint8_t duty_cycle)
{
        if (led == KNOB_G_CLICK_LED_ALL) {
                knob_G_click_led_write_reg(ctx, KNOB_REG_BRIGHTNESS_CONTROL_FOR_ALL_LED, &duty_cycle, 1);
        } else {
                ASSERT_WARNING(led <= KNOB_G_CLICK_LED_MAX);

                knob_G_click_led_write_reg(ctx, 0x09 + led, &duty_cycle, 1);
        }
}

void knob_G_click_led_set_gain(knob_G_click_led_cfg_t *ctx, KNOB_G_CLICK_LED led, uint8_t gain)
{
        if (led == KNOB_G_CLICK_LED_ALL) {
                knob_G_click_led_write_reg(ctx, KNOB_REG_GAIN_CONTROL_FOR_ALL_LED, &gain, 1);
        } else {
                ASSERT_WARNING(led <= KNOB_G_CLICK_LED_MAX);

                knob_G_click_led_write_reg(ctx, 0x21 + led, &gain, 1);
        }
}

void knob_G_click_led_hw_reset(knob_G_click_led_cfg_t *ctx)
{
        DBG_IO_OFF(KNOB_G_CLICK_RST_PORT, KNOB_G_CLICK_RST_PIN);
        OS_DELAY_MS(10);
        DBG_IO_ON(KNOB_G_CLICK_RST_PORT, KNOB_G_CLICK_RST_PIN);
        OS_DELAY_MS(10);

        knob_G_click_led_set_gain(ctx, KNOB_G_CLICK_LED_ALL, 0xFF);
}

#endif

