/**
 ****************************************************************************************
 *
 * @file cli_app_config.h
 *
 * @brief CLI APP configuration file
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

#ifndef CLI_APP_CONFIG_H_
#define CLI_APP_CONFIG_H_

#ifndef APP_CLI_DEEP_SLEEP_EN
#define APP_CLI_DEEP_SLEEP_EN   ( 1 )
#endif

#ifndef APP_CLI_HIBERNATION_EN
#define APP_CLI_HIBERNATION_EN  ( 1 )
#endif

#ifndef APP_CLI_POR_GPIO_EN
#define APP_CLI_POR_GPIO_EN     ( 1 )
#endif

#ifndef APP_CLI_RTC_EN
#define APP_CLI_RTC_EN          ( 1 )
#endif

#ifndef APP_DEFAULT_SLEEP_MODE
#define APP_DEFAULT_SLEEP_MODE  pm_mode_extended_sleep
#endif

#endif /* CLI_APP_CONFIG_H_ */
