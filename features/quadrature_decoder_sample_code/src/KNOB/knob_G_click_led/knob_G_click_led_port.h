/**
 ****************************************************************************************
 *
 * @file knob_G_click_led_port.h
 *
 * @brief PCA9956B LED driver support.
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

#ifndef KNOB_G_CLICK_LED_PORT_H_
#define KNOB_G_CLICK_LED_PORT_H_

#include "ad_i2c.h"
#include "sys_timer.h"
#include "knob_G_click_led.h"

/*
 * Application-defined routine that performs the actual I2C write transaction to the underlying LED driver.
 *
 * \param [in] dev  Handle of the I2C instance created to establish the communication with the PCA9956B LED driver.
 *
 * \param [in] reg  The register address to which the \p wbuf should be written to.
 *
 * \param [in] wbuf Pointer to buffer that contains the data to be written to \p reg.
 *
 * \param [in] wlen The number of bytes that should be read from \p wbuf and should be written
 *                  to the selected \p reg.
 *
 * \return The error code of the executed transaction. Currently the routine should always return
 *         zero, indicating success. Developers can modify the exhibited porting routine and
 *         return an error code in case of failure.
 *
 */
int app_knob_G_click_led_write_reg(void *dev, uint8_t reg, const uint8_t *wbuf, size_t wlen);

/*
 * Application-defined routine that performs the actual I2C read transaction to the underlying LED driver.
 *
 * \param [in] dev  Handle of the I2C instance created to establish the communication with the PCA9956B LED driver.
 *
 * \param [in] reg  The register address from which data should be read from.
 *
 * \param [in] rbuf Pointer to buffer that read data from \p reg should be stored to.
 *
 * \param [in] rlen The number of bytes that should be read from \p reg and should be stored to \p rbuf.
 *
 * \return The error code of the executed transaction. Currently the routine should always return
 *         zero, indicating success. Developers can modify the exhibited porting routine and
 *         return an error code in case of failure.
 *
 */
int app_knob_G_click_led_read_reg(void *handle, uint8_t reg, uint8_t *rbuf, size_t rlen);

/*
 * Application-defined routine to be called when the QDEC controller reports a movement.
 * Currently, three different states are supported which should reflect three different
 * LEDs pattern. Developers can modify that routine and provide support for more LEDs patterns.
 *
 * \param [in] dev         Handle of the I2C instance created to establish the communication with the PCA9956B LED driver.
 *
 * \param [in] key_state   An arbitrary unsigned number indicating the current LED state. Each state is solely defined
 *                         on application level and should reflect a unique LED pattern. Typically, a KEY state should
 *                         changed upon KNOB KEY event detection.
 *
 * \param [in] direction   A boolean to indicate if the KNOB is rotated clockwise or counterclockwise.
 *                         Direction assignment does not matter e.g. 1 can reflect clockwise movement
 *                         and 0 counterclockwise movement.
 *
 * \note Each supported \p key_state should 'retain' its state while switching from/to another KEY state.
 *
 */
void app_knob_G_click_led_update(knob_G_click_led_cfg_t *ctx, uint8_t key_state, bool direction);

#endif /* KNOB_G_CLICK_LED_PORT_H_ */
