/**
 ****************************************************************************************
 *
 * @file cli_hibernation.c
 *
 * @brief Hibernation shell operations
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

#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "hw_wkup.h"
#include "cli_hibernation.h"
#include "cli_app_config.h"

#if APP_CLI_HIBERNATION_EN
__RETAINED_RW static struct hibernation_cfg_t {
        HW_WKUP_HIBERN_PIN pin;
        HW_WKUP_HIBERN_POLARITY pol;
        bool status;
} hibernation_config = { 0, 0, 0 };

static const char *cli_hibernation_pin_info[] = {
        "P0.14 and P1.04 are disabled",
        "P0.14 can exit the device from hibernation",
        "P1.04 can exit the device from hibernation",
        "P0.14 and P1.04 can exit the device from hibernation"
};

static const char *cli_hibernation_pol_info[] = {
        "P0.14 and P1.04 is configured to active high",
        "P0.14 is configured to active low",
        "P1.04 is configured to active low",
        "P0.14 and P1.04 is configured to active low"
};

bool cli_hibernation_get_status(void)
{
        return hibernation_config.status;
}

void cli_hibernation_set_status_handler(int argc, const char *argv[], void *user_data)
{
        if (argc != 2) {
                DBG_PRINTF(FG_LRED "Invalid syntax - hibernation_set_status <status>, where"
                        DBG_NEW_LINE FG_GREEN " * <status>: <enable> or <disable>");
                return;
        }

        if (!strcmp("enable", argv[1])) {
                hibernation_config.status = true;
        } else if (!strcmp("disable", argv[1])) {
                hibernation_config.status = false;
        } else {
                DBG_PRINTF(FG_RED "Invalid status selection...");
        }
        DBG_PRINTF(DBG_NEW_LINE);
}

void cli_hibernation_get_info_handler(int argc, const char *argv[], void *user_data)
{
        DBG_PRINTF(FG_GREEN "%s, %s, Status: %s" DBG_NEW_LINE,
                cli_hibernation_pin_info[hibernation_config.pin],
                cli_hibernation_pol_info[hibernation_config.pol],
                hibernation_config.status ? "enabled" : "disabled");
}

void cli_hibernation_select_port_handler(int argc, const char *argv[], void *user_data)
{
        HW_WKUP_HIBERN_PIN pin;
        HW_WKUP_HIBERN_POLARITY pol;

        if (argc != 3) {
                DBG_PRINTF(FG_LRED "Invalid syntax - hibernation_sel_port <port> <pol>, where"
                        DBG_NEW_LINE "<port>: "
                        DBG_NEW_LINE FG_GREEN " * 0 to disable hibernation wake-up input source"
                        DBG_NEW_LINE FG_GREEN " * 1 to select P0.14"
                        DBG_NEW_LINE FG_GREEN " * 2 to select P1.04"
                        DBG_NEW_LINE FG_GREEN " * 3 to select both P0.14 and P1.04 input sources"
                        DBG_NEW_LINE "<pol>: "
                        DBG_NEW_LINE FG_GREEN "* 0 to set both P0.14 and P1.04 active high input sources"
                        DBG_NEW_LINE FG_GREEN "* 1 to set P0.14 active low input source"
                        DBG_NEW_LINE FG_GREEN "* 2 to set P1.04 active low input source"
                        DBG_NEW_LINE FG_GREEN "* 3 to set both P0.14 and P1.04 active low input sources" DBG_NEW_LINE);
                return;
        }
        pin = atoi(argv[1]); pol = atoi(argv[2]);

        if (pin > HW_WKUP_HIBERN_BOTH_PINS) {
                DBG_PRINTF(FG_CYAN "Pin selection out of range..." DBG_NEW_LINE);
                return;
        }
        if (pol > HW_WKUP_HIBERN_BOTH_PINS_ACTIVE_LOW) {
                DBG_PRINTF(FG_CYAN "Polarity selection out of range..." DBG_NEW_LINE);
                return;
        }

        hibernation_config.pol = pol;
        hibernation_config.pin = pin;

        /* Configure the WKUP hibernation block */
        hw_wkup_configure_hibernation(hibernation_config.pin, hibernation_config.pol);

        DBG_PRINTF(DBG_NEW_LINE);
}
#endif /* APP_CLI_HIBERNATION_EN */
