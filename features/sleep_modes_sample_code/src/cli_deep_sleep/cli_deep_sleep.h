/**
 ****************************************************************************************
 *
 * @file cli_deep_sleep.h
 *
 * @brief Deep sleep shell operations
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

#ifndef CLI_DEEP_SLEEP_H_
#define CLI_DEEP_SLEEP_H_

void cli_deep_sleep_set_status_handler(int argc, const char *argv[], void *user_data);
void cli_deep_sleep_select_port_handler(int argc, const char *argv[], void *user_data);
void cli_deep_sleep_reset_port_handler(int argc, const char *argv[], void *user_data);
void cli_deep_sleep_get_info_handler(int argc, const char *argv[], void *user_data);

/*
 * Get deep sleep status
 *
 * \return True is deep sleep is selected by users, false otherwise.
 *
 * \note The deep sleep mode should be enabled explicitly by application
 *       and not by the handler once users requested to do so.
 *       The reason for this is that, a sleeping mode of higher priority
 *       (typically the active or idle state) might be requested at that time
 *       which should prevent the device from entering the deep sleep mode.
 *       Application should make sure that the device is ready to enter the
 *       deep sleep mode.
 */
bool cli_deep_sleep_get_status(void);

#endif /* CLI_DEEP_SLEEP_H_ */
