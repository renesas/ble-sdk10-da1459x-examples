/**
 ****************************************************************************************
 *
 * @file cli_app.c
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

#include "misc.h"
#include "hw_wkup.h"
#include "hw_pdc.h"
#include "cli_app.h"
#include "sys_power_mgr.h"
#include "cli.h"

__RETAINED static cli_app_gpio0_callback cli_gpio0_cb;

static void app_wkup_gpio_p0_cb(void)
{
        uint32_t status;

        /* Get the status of the last wake-up event */
        status = hw_wkup_get_gpio_status(HW_GPIO_PORT_0);

        if (cli_gpio0_cb) {
                cli_gpio0_cb(status);
        }

        /* This function must be called so the status register is cleared!!! */
        hw_wkup_clear_gpio_status(HW_GPIO_PORT_0, status);
}

void cli_app_gpio0_register_cb(cli_app_gpio0_callback cb)
{
        cli_gpio0_cb = cb;
}

uint32_t cli_app_gpio_pdc_entry_add(HW_GPIO_PORT port, HW_GPIO_PIN pin)
{
        uint32_t pdc_idx;

        pdc_idx = hw_pdc_add_entry(HW_PDC_LUT_ENTRY_VAL(port, pin, HW_PDC_MASTER_CM33, 0));
        ASSERT_WARNING(pdc_idx != HW_PDC_INVALID_LUT_INDEX);

        hw_pdc_set_pending(pdc_idx);
        hw_pdc_acknowledge(pdc_idx);

        return pdc_idx;
}

void cli_app_gpio_pdc_entry_remove(uint32_t pdc_idx)
{
        hw_pdc_remove_entry(pdc_idx);
}

static void cli_wkup_init(void)
{
        /* Initialize the WKUP controller */
        hw_wkup_init(NULL);

#if dg_configUSE_CONSOLE
        /*
         * Configure CTS line's trigger polarity and mode based on the current state
         * as it might happen that the serial console is not enabled by the time
         * this routine is called.
         */
        hw_wkup_set_trigger(SER1_CTS_PORT, SER1_CTS_PIN,
                hw_gpio_get_pin_status(SER1_CTS_PORT, SER1_CTS_PIN) ?
                HW_WKUP_TRIG_EDGE_LO : HW_WKUP_TRIG_EDGE_HI);
#endif

        /* CTS_N is connected to P0.11 */
        hw_wkup_register_gpio_p0_interrupt(app_wkup_gpio_p0_cb, 1);

        /* Enable interrupts on WKUP controller */
        hw_wkup_enable_key_irq();

#if dg_configUSE_CONSOLE
        cli_app_gpio_pdc_entry_add(SER1_CTS_PORT, SER1_CTS_PIN);
#endif
}

static void cli_app_init(void)
{
        /* When the CONSOLE/CLI modules are enabled and because of the UART adapter invocation,
         * the device is only allowed to enter the idle sleep state (low-power WFI ARM state). */
        cli_init();
        cli_wkup_init();
}

DEVICE_INIT(cli_app, cli_app_init, NULL);
