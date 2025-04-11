/**
 ****************************************************************************************
 *
 * @file platform_devices.c
 *
 * @brief Configuration of devices connected to board data structures
 *
 * Copyright (c) 2022-2024 Renesas Electronics Corporation and/or its affiliates
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
***************************************************************************************
 */

#include <ad_spi.h>
#include "peripheral_setup.h"
#include "platform_devices.h"

/*
 * PLATFORM PERIPHERALS GPIO CONFIGURATION
 *****************************************************************************************
 */

/* SPI chip-select pins */
static ad_io_conf_t cs_MCP4921[] = {{

        .port = MCP4921_CS_PORT,
        .pin  = MCP4921_CS_PIN,
        .on = {
                .mode     = HW_GPIO_MODE_OUTPUT,
                .function = HW_GPIO_FUNC_GPIO,
                .high     = true
        },
        .off = {
                .mode     = HW_GPIO_MODE_OUTPUT,
                .function = HW_GPIO_FUNC_GPIO,
                .high     = true
               },}
};

/* SPI1 IO */
static const ad_spi_io_conf_t bus_MCP4921 = {

        .spi_do = {
                .port = MCP4921_DO_PORT,
                .pin  = MCP4921_DO_PIN,
                .on   = {HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_SPI_DO, false},
                .off  = {HW_GPIO_MODE_INPUT,            HW_GPIO_FUNC_GPIO,   true},
        },
        .spi_di = { // Not required
                .port = MCP4921_DI_PORT,
                .pin  = MCP4921_DI_PIN,
                .on   = {HW_GPIO_MODE_INPUT, HW_GPIO_FUNC_SPI_DI, false},
                .off  = {HW_GPIO_MODE_INPUT, HW_GPIO_FUNC_GPIO,   true},
        },
        .spi_clk = {
                .port = MCP4921_CLK_PORT,
                .pin  = MCP4921_CLK_PIN,
                .on   = {HW_GPIO_MODE_OUTPUT_PUSH_PULL, HW_GPIO_FUNC_SPI_CLK, false},
                .off  = {HW_GPIO_MODE_INPUT,            HW_GPIO_FUNC_GPIO,    true},
        },

        /*
         * The number of pins in spi_master_cs array.
         *
         */
        .cs_cnt = 1,
        .spi_cs = cs_MCP4921,
};

/* External sensor/module SPI driver */
static const ad_spi_driver_conf_t drv_MCP4921 = {
        .spi = {
                .cs_pad         = { MCP4921_CS_PORT, MCP4921_CS_PIN },
                .word_mode      = HW_SPI_WORD_16BIT,    /* Required by the module used */
                .smn_role       = HW_SPI_MODE_MASTER,
                .cpol_cpha_mode  = HW_SPI_CP_MODE_3,
                .xtal_freq      = 16,    /* Operating freq. @ DIVN / xtal_freq = 4MHz */
                .fifo_mode      = HW_SPI_FIFO_RX_TX,
                .disabled       = 0,                    /* Should be disabled during initialization phase */
                .spi_cs         = HW_SPI_CS_GPIO,
                .rx_tl = HW_SPI_FIFO_LEVEL0,
                .tx_tl = HW_SPI_FIFO_LEVEL0,
                .swap_bytes = false,
                .select_divn = true,
                .use_dma = true,
                .rx_dma_channel = HW_DMA_CHANNEL_0,
                .tx_dma_channel = HW_DMA_CHANNEL_0 + 1,
        }
};
/* Sensor/module device configuration */
const ad_spi_controller_conf_t dev_MCP4921 = {
        .id  = HW_SPI1,
        .io  = &bus_MCP4921,
        .drv = &drv_MCP4921,
};

spi_device MCP4921_DEVICE = &dev_MCP4921;
