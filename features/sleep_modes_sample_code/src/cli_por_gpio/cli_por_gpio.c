/**
 ****************************************************************************************
 *
 * @file cli_por_gpio.c
 *
 * @brief PoR from GPIO shell operations
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
#include <string.h>
#include <stdlib.h>
#include "misc.h"
#include "hw_sys.h"
#include "cli_por_gpio.h"
#include "cli_app_config.h"

#if APP_CLI_POR_GPIO_EN
__RETAINED_RW static struct por_gpio_cfg_t {
        HW_GPIO_PORT port;
        HW_GPIO_PIN pin;
        bool pol;
        uint8_t timeout;
} por_gpio_config = { HW_GPIO_PORT_MAX, HW_GPIO_PIN_MAX, 0, 0x18 };

void cli_por_gpio_get_info_handler(int argc, const char *argv[], void *user_data)
{
        if (por_gpio_config.port < HW_GPIO_PORT_MAX && por_gpio_config.pin < HW_GPIO_PIN_MAX) {
                DBG_PRINTF(FG_GREEN "P%d.%d, %s, Raw timeout: %d",
                        por_gpio_config.port, por_gpio_config.pin,
                        por_gpio_config.pol ? "active_high" :
                                              "active_low", por_gpio_config.timeout);
        } else {
                DBG_PRINTF(FG_GREEN "Invalid port selection" DBG_NEW_LINE);
        }
}

void cli_por_gpio_select_port_handler(int argc, const char *argv[], void *user_data)
{
        HW_GPIO_PORT port;
        HW_GPIO_PIN pin;
        bool pol;

        if (argc != 4) {
                DBG_PRINTF(FG_LRED "Invalid syntax - por_gpio_sel_port <port> <pin> <pol>, where "
                        DBG_NEW_LINE FG_GREEN " * <port>: <p0> or <p1>. In case of invalid value,"
                                                  "the current port selection will be disabled."
                        DBG_NEW_LINE FG_GREEN " * <pin>: A pin number of the selected port from [0..15]. In case of"
                                                  "invalid value, the current port selection will be disabled."
                        DBG_NEW_LINE FG_GREEN " * <pol>: <active_low> or <active_high>");
                return;
        }

        if (!strcmp("p0", argv[1])) {
                port = 0;
        } else if (!strcmp("p1", argv[1])) {
                port = 1;
        } else {
                port = HW_GPIO_PORT_MAX;
        }

        pin = atoi(argv[2]);

        if (!strcmp("active_low", argv[3])) {
                pol = false;
        } else if (!strcmp("active_high", argv[3])) {
                pol = true;
        } else {
                DBG_PRINTF(FG_RED "Invalid polarity selection..." DBG_NEW_LINE);
                return;
        }

        if (port >= HW_GPIO_PORT_MAX || pin >= hw_gpio_port_num_pins[port]) {
                DBG_PRINTF(FG_CYAN "Invalid GPIO selection. PoR from GPIO will be disabled..." DBG_NEW_LINE);
        }

        if (port != por_gpio_config.port || pin != por_gpio_config.pin ||
                                                  por_gpio_config.pol != pol) {

                hw_gpio_set_pin_function(port, pin,
                        pol ? HW_GPIO_MODE_INPUT_PULLDOWN : HW_GPIO_MODE_INPUT_PULLUP, HW_GPIO_FUNC_GPIO);
                hw_gpio_pad_latch_enable(port, pin);
                hw_gpio_pad_latch_disable(port, pin);

                /* Overwrite previous GPIO selection */
                por_gpio_config.port = port;
                por_gpio_config.pin = pin;
                por_gpio_config.pol = pol;

                /* Polarity will be set even if the selected port is invalid */
                hw_gpio_configure_por_pin(por_gpio_config.port,
                                por_gpio_config.pin, por_gpio_config.pol);
        }

        DBG_PRINTF(DBG_NEW_LINE);
}

void cli_por_gpio_set_timeout_handler(int argc, const char *argv[], void *user_data)
{
        int timeout;

        if (argc != 2) {
                DBG_PRINTF(FG_LRED "Invalid syntax - por_gpio_set_timeout <timeout>, where "
                        DBG_NEW_LINE FG_GREEN " * <timeout>: [0..0x7F] - The actual timeout is <timeout> * 4096 * RCLP period");
                return;
        }

        /* Get timeout event */
        timeout = atoi(argv[1]);
        if (timeout >= REG_MSK(CRG_TOP, POR_TIMER_REG, POR_TIME)) {
                DBG_PRINTF(FG_CYAN "Argument value out of range..." DBG_NEW_LINE);
                return;
        }
        por_gpio_config.timeout = (uint8_t)timeout;

        hw_sys_set_por_timer(por_gpio_config.timeout);

        DBG_PRINTF(DBG_NEW_LINE);
}
#endif /* APP_CLI_POR_GPIO_EN */
