/**
 ****************************************************************************************
 *
 * @file peripheral_setup.h
 *
 * @brief File that includes all I/O pins definitions
 *
 * Copyright (C) 2020-2025 Renesas Electronics Corporation and/or its affiliates.
 * This computer program includes Confidential, Proprietary Information
 * of Renesas Electronics Corporation and/or its affiliates. All Rights Reserved.
 *
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
