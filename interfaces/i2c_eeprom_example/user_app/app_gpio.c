/**
 ****************************************************************************************
 *
 * @file app_gpio.c
 *
 * @brief Basic framework to handle I/O pins outside adapter context.
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

#include "hw_sys.h"
#include "app_gpio.h"

void app_gpio_set_active(const ad_io_conf_t *io, uint8_t size)
{
#if !dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE
        /* GPIO controller resides in PD_COM and so it should be enabled before
         * accessing any GPIO. */
        hw_sys_pd_com_enable();
#endif

        ad_io_configure(io, size, AD_IO_CONF_ON);

        ad_io_set_pad_latch(io, size, APP_GPIO_DYNAMIC_MODE ? AD_IO_PAD_LATCHES_OP_TOGGLE :
                                                              AD_IO_PAD_LATCHES_OP_ENABLE);

#if !dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE && APP_GPIO_DYNAMIC_MODE
        /* When PD_COM is not needed it should be disabled to minimize power consumption
         * when in the sleep state. */
        hw_sys_pd_com_disable();
#endif /* dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE */
}

void app_gpio_set_inactive(const ad_io_conf_t *io, uint8_t size)
{
#if !dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE && APP_GPIO_DYNAMIC_MODE
        /* GPIO controller resides in PD_COM and so it should be enabled before
         * accessing any GPIO. */
        hw_sys_pd_com_enable();
#else
        ASSERT_WARNING(hw_pd_check_com_status());
#endif

        ad_io_configure(io, size, AD_IO_CONF_OFF);

        ad_io_set_pad_latch(io, size, APP_GPIO_DYNAMIC_MODE ? AD_IO_PAD_LATCHES_OP_TOGGLE :
                                                              AD_IO_PAD_LATCHES_OP_DISABLE);

#if !dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE
        /* When PD_COM is not needed it should be disabled to minimize power consumption
         * when in the sleep state. */
        hw_sys_pd_com_disable();
#endif
}
