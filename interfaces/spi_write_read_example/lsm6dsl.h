/*
 ****************************************************************************************
 * @file lsm6dsl.h
 *
 * @brief Register addresses of LSM6DSL
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

#ifndef LSM6DSL_H_
#define LSM6DSL_H_

#include <stdio.h>

// LSM6DSL Register Definition
const uint16_t LSM6DSL_CMD_READ     = 0x80;
const uint16_t LSM6DSL_WHO_AM_I     = 0x0F;
const uint16_t LSM6DSL_CTRL1_XL     = 0x10;
const uint16_t LSM6DSL_CTRL2_G      = 0x11;
const uint16_t LSM6DSL_OUTX_L_G_REG = 0x22;    // Gyroscope X-axis low byte register
const uint16_t LSM6DSL_OUTY_L_G_REG = 0x24;    // Gyroscope Y-axis low byte register
const uint16_t LSM6DSL_OUTZ_L_G_REG = 0x26;    // Gyroscope Z-axis low byte register
const uint16_t LSM6DSL_OUTX_L_XL    = 0x28;    // Accelerometer X-axis low byte register
const uint16_t LSM6DSL_OUTY_L_XL    = 0x2A;    // Accelerometer Y-axis low byte register
const uint16_t LSM6DSL_OUTZ_L_XL    = 0x2C;    // Accelerometer Z-axis low byte register
const uint16_t LSM6DSL_STATUS_REG   = 0x1E;    // Status register
const uint16_t LSM6DSL_CTRL3_C      = 0x12;    // Control register 3
const uint16_t LSM6DSL_CTRL4_C      = 0x13;    // Control register 4
const uint16_t LSM6DSL_CTRL5_C      = 0x14;    // Control register 5
const uint16_t LSM6DSL_FIFO_CTRL1   = 0x06;    // FIFO control register 1
const uint16_t LSM6DSL_FIFO_CTRL2   = 0x07;    // FIFO control register 2
const uint16_t LSM6DSL_FIFO_CTRL3   = 0x08;    // FIFO control register 3
const uint16_t LSM6DSL_INT1_CTRL    = 0x0D;    // Interrupt control register 1
const uint16_t LSM6DSL_INT2_CTRL    = 0x0E;    // Interrupt control register 2

#endif /* LSM6DSL_H_ */
