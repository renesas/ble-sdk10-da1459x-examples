/**
 ****************************************************************************************
 *
 * @file knob_G_click_key.c
 *
 * @brief Source file to support KEY (push button) events of KNOB G CLICK.
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
#include "sys_power_mgr.h"
#include "knob_G_click_key.h"
#include "knob_G_click_config.h"

#if (KNOB_G_CLICK_KEY_ENABLE == 1)

__RETAINED static knob_G_click_key_callback_t callback;

void knob_G_click_key_register_cb(knob_G_click_key_callback_t user_cb)
{
        callback = user_cb;
}

static void knob_G_click_key_cb(HW_GPIO_PORT port)
{
        uint32_t status;

        /* Get the status of the last wake-up event */
        status = hw_wkup_get_gpio_status(port);

        /* User should process the KEY event */
        if (callback) {
                callback(port, status);
        }

        /* This function must be called so the status register is cleared!!! */
        hw_wkup_clear_gpio_status(port, status);
}

#if (QDEC_KEY_PORT == HW_GPIO_PORT_0)
static void knob_G_click_key_p0_cb(void)
{
        knob_G_click_key_cb(HW_GPIO_PORT_0);
}
#else
static void knob_G_click_key_p1_cb(void)
{
        knob_G_click_key_cb(HW_GPIO_PORT_1);
}
#endif

static uint32_t knob_G_click_key_add_pdc_entry(HW_GPIO_PORT port, HW_GPIO_PIN pin)
{
        uint32_t pdc_idx;

        pdc_idx = hw_pdc_add_entry(HW_PDC_LUT_ENTRY_VAL(port, pin, HW_PDC_MASTER_CM33, 0));
        ASSERT_WARNING(pdc_idx != HW_PDC_INVALID_LUT_INDEX);

        hw_pdc_set_pending(pdc_idx);
        hw_pdc_acknowledge(pdc_idx);

        return pdc_idx;
}

static void knob_G_click_key_init(void *data)
{
        (void)data;

        /* Initialize the WKUP controller */
        hw_wkup_init(NULL);

        /*
         * The WKUP should initially be configured based on the selected active edge.
         * User can then toggle the active edge within the registered callback.
         */
        hw_wkup_set_trigger(KNOB_G_CLICK_KEY_PORT, KNOB_G_CLICK_KEY_PIN,
                KNOB_G_CLICK_KEY_ACTIVE_LOW ? HW_WKUP_TRIG_EDGE_LO : HW_WKUP_TRIG_EDGE_HI);

#if (QDEC_KEY_PORT == HW_GPIO_PORT_0)
        hw_wkup_register_gpio_p0_interrupt(knob_G_click_key_p0_cb, 1);
#else
        hw_wkup_register_gpio_p1_interrupt(knob_G_click_key_p1_cb, 1);
#endif

        /* Enable interrupts on WKUP controller */
        hw_wkup_enable_key_irq();

        knob_G_click_key_add_pdc_entry(KNOB_G_CLICK_KEY_PORT, KNOB_G_CLICK_KEY_PIN);
}

DEVICE_INIT(app_qdec_key, knob_G_click_key_init, NULL);

#endif
