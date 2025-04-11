/**
 ****************************************************************************************
 *
 * @file cli_app.h
 *
 * @brief CLI APP operations
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

#ifndef CLI_APP_H_
#define CLI_APP_H_

#include <stdio.h>
#include "hw_gpio.h"
#include "hw_pdc.h"

typedef void (*cli_app_gpio0_callback)(uint32_t status);

void cli_app_gpio_pdc_entry_remove(uint32_t pdc_idx);
uint32_t cli_app_gpio_pdc_entry_add(HW_GPIO_PORT port, HW_GPIO_PIN pin);

/*
 * User callback function to be called upon WKUP GPIO0 event
 *
 * \param [in] cb User callback function to be called upon WKUP event on PORT0.
 *                Setting to NULL will result in unregistering any
 *                previous callback function.
 *
 * \note The callback function will be called within ISR interrupt and so
 *       callback should be as fast as possible. In case of tasks, these
 *       should be deferred by sending notifications to the application
 *       task.
 */
void cli_app_gpio0_register_cb(cli_app_gpio0_callback cb);


#endif /* CLI_APP_H_ */
