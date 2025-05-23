/**
 ****************************************************************************************
 *
 * @file periph_setup.h
 *
 * @brief Configuration of devices connected to board
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

#ifndef PERIPHERAL_SETUP_H_
#define PERIPHERAL_SETUP_H_

#define LSM6DSL_DO_PORT      ( HW_GPIO_PORT_0 )
#define LSM6DSL_DO_PIN       ( HW_GPIO_PIN_2 )

#define LSM6DSL_DI_PORT      ( HW_GPIO_PORT_0 )
#define LSM6DSL_DI_PIN       ( HW_GPIO_PIN_3 )

#define LSM6DSL_CLK_PORT     ( HW_GPIO_PORT_0 )
#define LSM6DSL_CLK_PIN      ( HW_GPIO_PIN_0 )

#define LSM6DSL_CS_PORT      ( HW_GPIO_PORT_0 )
#define LSM6DSL_CS_PIN       ( HW_GPIO_PIN_1 )

#endif /* PERIPHERAL_SETUP_H_ */
