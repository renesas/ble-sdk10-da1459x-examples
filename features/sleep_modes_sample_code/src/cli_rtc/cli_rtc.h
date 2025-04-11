/**
 ****************************************************************************************
 *
 * @file cli_rtc.h
 *
 * @brief RTC shell operations
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

#ifndef CLI_RTC_H_
#define CLI_RTC_H_

#include "hw_rtc.h"

#ifndef APP_RTC_MODE_24H
#define APP_RTC_MODE_24H    ( 1 )
#endif

#ifndef APP_RTC_12H_PM
#define APP_RTC_12H_PM  ( 0 )
#endif

#ifndef APP_RTC_HSEC
#define APP_RTC_HSEC    ( 0 )
#endif

#ifndef APP_RTC_SEC
#define APP_RTC_SEC     ( 0 )
#endif

#ifndef APP_RTC_MIN
#define APP_RTC_MIN     ( 0 )
#endif

#ifndef APP_RTC_HOUR
#define APP_RTC_HOUR    ( 0 )
#endif

#ifndef APP_RTC_MONTH
#define APP_RTC_MONTH   ( 1 )
#endif

#ifndef APP_RTC_MDAY
#define APP_RTC_MDAY    ( 1 )
#endif

#ifndef APP_RTC_YEAR
#define APP_RTC_YEAR    ( 2025 )
#endif

#ifndef APP_RTC_WDAY
#define APP_RTC_WDAY    ( 1 )
#endif

typedef void (*cli_rtc_alarm_callback)(void);

void cli_rtc_time_get_handler(int argc, const char *argv[], void *user_data);
void cli_rtc_time_set_handler(int argc, const char *argv[], void *user_data);
void cli_rtc_alarm_set_handler(int argc, const char *argv[], void *user_data);
void cli_rtc_alarm_get_handler(int argc, const char *argv[], void *user_data);

/*
 * User callback function to be called upon alarm event
 *
 * \param [in] cb User callback function to be called upon alarm event.
 *                Setting to NULL will result in unregistering any
 *                previous callback function.
 *
 * \note The callback function will be called within ISR interrupt and so
 *       callback should be as fast as possible. In case of tasks, these
 *       should be deferred by sending notifications to the application
 *       task.
 */
void cli_rtc_alarm_register_cb(cli_rtc_alarm_callback cb);

#endif /* CLI_RTC_H_ */
