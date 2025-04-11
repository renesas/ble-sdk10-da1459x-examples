/**
 ****************************************************************************************
 *
 * @file platform_devices.h
 *
 * @brief Configuration of devices connected to board
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

#ifndef PLATFORM_DEVICES_H_
#define PLATFORM_DEVICES_H_

#include "ad.h"

extern ad_io_conf_t led1_cfg[];
extern size_t led1_size;

#define LED1_DEVICE  led1_cfg
#define LED1_SIZE led1_size

#endif /* PLATFORM_DEVICES_H_ */

