/**
 ****************************************************************************************
 *
 * @file misc.h
 *
 * @brief Miscellaneous functionality
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

#ifndef MISC_H_
#define MISC_H_

#include <stdio.h>
#include "hw_gpio.h"

/*********************************************************************
 *
 *       Defines
 *
 *********************************************************************
 */
#define KiB    1024

#if DBG_LOG_ENABLE
   #define DBG_LOG(_f, args...)   printf((_f), ## args)
#else
   #define DBG_LOG(_f, args...)
#endif /* DBG_LOG_ENABLE */

#if DBG_IO_ENABLE
   #define DBG_IO_ON(_port, _pin)                                                                    \
        {                                                                                          \
                hw_sys_pd_com_enable();                                                            \
                hw_gpio_set_pin_function((_port), (_pin), HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO); \
                hw_gpio_set_active((_port), (_pin));                                               \
                hw_gpio_pad_latch_enable((_port), (_pin));                                         \
                hw_gpio_pad_latch_disable((_port), (_pin));                                        \
                hw_sys_pd_com_disable();                                                           \
        }

   #define DBG_IO_OFF(_port, _pin)                                                                   \
        {                                                                                          \
                hw_sys_pd_com_enable();                                                            \
                hw_gpio_set_pin_function((_port), (_pin), HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO); \
                hw_gpio_set_inactive((_port), (_pin));                                             \
                hw_gpio_pad_latch_enable((_port), (_pin));                                         \
                hw_gpio_pad_latch_disable((_port), (_pin));                                        \
                hw_sys_pd_com_disable();                                                           \
        }

#else
   #define DBG_IO_ON(_port, _pin)
   #define DBG_IO_OFF(_port, _pin)
#endif /* DBG_IO_ENABLE */

#endif /* MISC_H_ */
