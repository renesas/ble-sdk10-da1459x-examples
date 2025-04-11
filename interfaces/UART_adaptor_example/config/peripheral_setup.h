/**
 ****************************************************************************************
 *
 * @file peripheral_setup.h
 *
 * @brief File that includes all I/O pins definitions
 *
 * Copyright (C) 2020-2024 Renesas Electronics Corporation and/or its affiliates
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

#include "hw_gpio.h"

#ifndef CONFIG_PERIPHERAL_SETUP_H_
#define CONFIG_PERIPHERAL_SETUP_H_

#define UART1_RX_PORT           ( HW_GPIO_PORT_0 )
#define UART1_RX_PIN            ( HW_GPIO_PIN_7 )
#define UART1_TX_PORT           ( HW_GPIO_PORT_0 )
#define UART1_TX_PIN            ( HW_GPIO_PIN_8 )

#define UART2_RX_PORT           ( HW_GPIO_PORT_1 )
#define UART2_RX_PIN            ( HW_GPIO_PIN_7 )
#define UART2_TX_PORT           ( HW_GPIO_PORT_1 )
#define UART2_TX_PIN            ( HW_GPIO_PIN_8 )
#define UART2_RTS_PORT          ( HW_GPIO_PORT_1 )
#define UART2_RTS_PIN           ( HW_GPIO_PIN_10 )
#define UART2_CTS_PORT          ( HW_GPIO_PORT_1 )
#define UART2_CTS_PIN           ( HW_GPIO_PIN_12 )



#endif /* CONFIG_PERIPHERAL_SETUP_H_ */
