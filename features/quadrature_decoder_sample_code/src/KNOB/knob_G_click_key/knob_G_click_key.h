/**
 ****************************************************************************************
 *
 * @file knob_G_click_key.h
 *
 * @brief Header file to support KEY (push button) events of KNOB G CLICK.
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

#ifndef KNOB_G_CLICK_KEY_H_
#define KNOB_G_CLICK_KEY_H_

/*
 * Pointer to user-defined function that should be called upon KNOB KEY events reported
 * by the WKUP controller.
 */
typedef void (*knob_G_click_key_callback_t)(HW_GPIO_PORT port, uint32_t status);

/*
 * @brief API to register a uder-defined callback function to be called upon KNOB KEY events.
 *
 * \param [in] user_cb Registered callback function.
 *
 * \note The callback function is called from within ISR and so its time execution
 *       should be as short as possible. Therefore, time-consuming operations
 *       should be deferred to a task using RTOS notifications/events.
 *
 */
void knob_G_click_key_register_cb(knob_G_click_key_callback_t user_cb);

#endif /* KNOB_G_CLICK_KEY_H_ */
