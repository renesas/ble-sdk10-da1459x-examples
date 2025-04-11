/**
 ****************************************************************************************
 *
 * @file knob_G_click_led_port.c
 *
 * @brief This file should contain the routines required to port the PCA9956B LED driver
 *        provided in knob_G_click_led files.
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

#include "osal.h"
#include "ad_i2c.h"
#include "sys_timer.h"
#include "knob_G_click_led_port.h"
#include "knob_G_click_config.h"
#include "knob_G_click_led.h"

#if (KNOB_G_CLICK_LED_ENABLE == 1)

__RETAINED static uint16_t i2c_transferred;

/*
 * Callback function called once a non-blocking I2C transaction is complete.
 * The callback is called from interrupt context and so we should not spend
 * too much time here.
 */
static void app_i2c_cb_preempt(void *user_data, HW_I2C_ABORT_SOURCE error)
{
        *((uint16_t *)user_data) = error;
}

/* Helper function to perform a non-blocking I2C write operation with timeout */
static void app_i2c_write_preempt(void *handle, const uint8_t *wbuf, size_t wlen, uint8_t flags,
                                                                                uint64_t timeout)
{
              i2c_transferred = (uint16_t)-1;
              uint64_t cur_timeout_tick = sys_timer_get_uptime_ticks();

              ad_i2c_write_async(handle, wbuf, wlen, app_i2c_cb_preempt,
                                                        &i2c_transferred, flags);
              while (i2c_transferred == (uint16_t)-1) {
                      if (sys_timer_get_uptime_ticks() - cur_timeout_tick > timeout) {
                              break;
                      }
                      OS_DELAY_MS(5);
              }
}

/* Helper function to perform a non-blocking I2C read operation with timeout */
static void app_i2c_write_read_preempt(void *handle, uint8_t *wbuf, size_t wlen, uint8_t *rbuf,
                                                    size_t rlen, uint8_t flags, uint64_t timeout)
{
              i2c_transferred = (uint16_t)-1;
              uint64_t cur_timeout_tick = sys_timer_get_uptime_ticks();

              ad_i2c_write_read_async(handle, wbuf, wlen, rbuf, rlen,
                                        app_i2c_cb_preempt, &i2c_transferred, flags);
              while (i2c_transferred == (uint16_t)-1) {
                      if (sys_timer_get_uptime_ticks() - cur_timeout_tick > timeout) {
                              break;
                      }
                      OS_DELAY_MS(5);
              }
}

/* Callback function to perform a write access to the TMP102 sensor */
int app_knob_G_click_led_write_reg(void *dev, uint8_t reg, const uint8_t *wbuf, size_t wlen)
{
        uint8_t tx_buf[ 256 ];
        ASSERT_WARNING(wlen < sizeof(tx_buf));

        /*
         * The first byte should be the address pointer that indicates which register
         * should respond to the write access.
         */
        tx_buf[ 0 ] = reg;

        /* Then copy the actual information that should be written to the address pointer provided. */
        for (int i = 1; i <= wlen; i++) {
                tx_buf[ i ] = wbuf[ i - 1 ];
        }

        /* Employ the I2C adapter to perform the actual write access */
        app_i2c_write_preempt(dev, tx_buf, wlen + 1, HW_I2C_F_ADD_STOP, OS_EVENT_FOREVER);

        return 0;
}

/* Callback function to perform a read access to the TMP102 sensor */
int app_knob_G_click_led_read_reg(void *handle, uint8_t reg, uint8_t *rbuf, size_t rlen)
{
        /* Employ the I2C adapter to perform the actual read access */
        app_i2c_write_read_preempt(handle, &reg, 1, rbuf, rlen,
                        HW_I2C_F_ADD_RESTART | HW_I2C_F_ADD_STOP, OS_EVENT_FOREVER);

        return 0;
}

void app_knob_G_click_led_update(knob_G_click_led_cfg_t *ctx, uint8_t key_state, bool direction)
{
        direction = !direction;

        switch (key_state) {
        case 0:
        {
                /* Static attribute so that brightness is resumed from the last duty cycle. */
                static uint8_t cnt = 0;

                knob_G_click_led_set_brightness(ctx, KNOB_G_CLICK_LED_ALL, cnt);
                /* The max. available duty cycle is 256 */
                cnt = cnt + (direction ? 1 : -1);
        }
                break;
        case 1:
        {
                /* Static attribute so that led position is resumed from the last position. */
                static uint8_t led_position = KNOB_G_CLICK_LED_1;

                if (led_position > KNOB_G_CLICK_LED_MAX) {
                        led_position = KNOB_G_CLICK_LED_1;
                } else if (led_position < KNOB_G_CLICK_LED_1) {
                        led_position = KNOB_G_CLICK_LED_MAX;
                }

                if (direction) {
                        knob_G_click_led_turn_on(ctx, led_position);
                        knob_G_click_led_turn_off(ctx,
                                led_position == KNOB_G_CLICK_LED_1 ? KNOB_G_CLICK_LED_MAX : led_position - 1);
                } else {
                        knob_G_click_led_turn_on(ctx, led_position);
                        knob_G_click_led_turn_off(ctx,
                                led_position == KNOB_G_CLICK_LED_MAX ? KNOB_G_CLICK_LED_1 : led_position + 1);
                }

                led_position = led_position + (direction ? 1 : -1);
        }
                break;
        case 2:
        {
                /* Static attribute so that led position is resumed from the last position. */
                static uint8_t led_position = KNOB_G_CLICK_LED_1;

                if (led_position > KNOB_G_CLICK_LED_MAX) {
                        led_position = KNOB_G_CLICK_LED_1;
                } else if (led_position < KNOB_G_CLICK_LED_1) {
                        led_position = KNOB_G_CLICK_LED_MAX;
                }

                if (direction) {
                        knob_G_click_led_turn_on(ctx, led_position);
                } else {
                        knob_G_click_led_turn_off(ctx,
                                led_position == KNOB_G_CLICK_LED_MAX ? KNOB_G_CLICK_LED_1 : led_position + 1);
                }

                led_position = led_position + (direction ? 1 : -1);
        }
                break;
        default:
                break;
        }
}

#endif
