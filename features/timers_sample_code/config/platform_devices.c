/**
 ****************************************************************************************
 *
 * @file platform_devices.c
 *
 * @brief Configuration of devices connected to board.
 *
 * Copyright (C) 2017-2023 Renesas Electronics Corporation and/or its affiliates
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

#include "hw_timer.h"
#include "osal.h"
#include "platform_devices.h"
#include "periph_setup.h"

timer_config app_timer_cfg = {
        /*
         * Select the clock path
         *
         * \note In case the fast clock is selected and the sleep mode is set to extended mode,
         *       the fast clock will be switched to slow clock before the system enters sleep.
         *       (the XTAL32M crystal is turned off during sleep). If this is the case, then it
         *       is suggested you to select the slow clock as it is difficult to determine the
         *       exact time the clock switching takes place.
         */
        .clk_src = HW_TIMER_CLK_SRC_INT,

        /*
         * Counter frequency =  (clk_src / (pre-scaler + 1))
         *
         * \note Max allowable pre-scaler is 0x1F. */
        .prescaler = 0,

        .mode = HW_TIMER_MODE_TIMER,

        .timer = {
                .direction = HW_TIMER_DIR_DOWN,

                /*
                 * When counting down, counter's value is automatically reloaded to reload_val,
                 * as soon as the counter reaches zero. If enabled, an interrupt is issued.
                 *
                 * When counting up, an IRQ is fired when the reload_val value is reached. However,
                 * the counter keeps counting and wraps around only when reaching its maximum
                 * value (2^24)
                 */
                .reload_val = 0,

                .free_run = true,

#if APP_TIMER_CAPTURE_EN
                .gpio1 = APP_TIMER_CAPTURE_PORT,
                .trigger1 = APP_TIMER_CAPTURE_EDGE ? HW_TIMER_TRIGGER_RISING : HW_TIMER_TRIGGER_FALLING,
                .gpio2 = APP_TIMER_CAPTURE_PORT,
                .trigger2 = APP_TIMER_CAPTURE_EDGE ? HW_TIMER_TRIGGER_FALLING : HW_TIMER_TRIGGER_RISING,

                /* HW_TIMER supports up to four capture channels compared to other instances that can
                 * support up to two capture channels. */
#endif
        },

        /* Configure PWM functionality */
        .pwm = {
                .port = APP_TIMER_PWM_PORT,
                .pin  = APP_TIMER_PWM_PIN,

                /* When set to true, TIMER will keep generating PWM pulses on P0_12 pin in the sleep state. */
                .pwm_active_in_sleep = true,

                /*
                 * PWM frequency = (output counter frequency after pre-scaling / (frequency + 1))
                 *
                 * \note If counter's pr-escaler has been set to maximum value (0x1F), PWM clock divider
                 *       has no further effect and \p frequency defines the PWM period expressed in
                 *       timer ticks.
                 */
                .frequency = 15,

                /*
                 * duty cycle ON = (duty_cycle / (frequency + 1))
                 *
                 * \note If counter's pre-scaler has been set to maximum value (0x1F), duty_cycle defines
                 *       the PWM duty cycle ON expressed in timer ticks.
                 *
                 */
                .duty_cycle = 7
        }
};
