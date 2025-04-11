/**
 ****************************************************************************************
 *
 * @file custom_config_eflash.h
 *
 * @brief Board Support Package. User Configuration file for cached eFLASH mode.
 *
 * Copyright (C) 2020-2025 Renesas Electronics Corporation and/or its affiliates
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
#ifndef CUSTOM_CONFIG_EFLASH_H_
#define CUSTOM_CONFIG_EFLASH_H_

#include "bsp_definitions.h"

#define USE_PARTITION_TABLE_EFLASH_WITH_SUOTA

/*************************************************************************************************\
 * System configuration
 */
#define dg_configEXEC_MODE                      ( MODE_IS_CACHED )
#define dg_configCODE_LOCATION                  ( NON_VOLATILE_IS_EMBEDDED_FLASH )

#define dg_configUSE_WDOG                       ( 1 )
#define dg_configUSE_SW_CURSOR                  ( 1 )

/*************************************************************************************************\
 * FreeRTOS configuration
 */
#define OS_FREERTOS                             /* Define this to use FreeRTOS */
#define configTOTAL_HEAP_SIZE                   ( 20 * 1024 )   /* FreeRTOS Total Heap Size */

/*************************************************************************************************\
 * Peripherals configuration
 */
#define dg_configNVMS_VES                       ( 0 )
#define dg_configNVPARAM_ADAPTER                ( 1 )

#define dg_configUART_ADAPTER                   ( 1 )     /* Enable the UART Adapter abstraction layer and API */

/* Enable circular DMA so no data are overwritten in the RX HW FIFOs upon file transfers. */
#define dg_configUART_RX_CIRCULAR_DMA           ( 1 )
/* This value has been adjusted so that no data loss is encountered in file transfer operations. */
#define dg_configUART2_RX_CIRCULAR_DMA_BUF_SIZE ( 1024 )

#if (dg_configUART_ADAPTER == 1)
#undef CONFIG_RETARGET
/*
 * Use the RTT mechanism to interact with the outside world e.g. log messages.
 * RETARGET operations employ the serial port which should raise conflicts
 * with the SUOSERIAL service.
 */
// #define CONFIG_RTT
#endif

#define dg_configSUOUART_SUPPORT                 ( 1 )

#if (dg_configSUOUART_SUPPORT == 1)
/*
 * Once the SUOUART task is executed there will be no time for lower
 * priority tasks (typically that should be the idle task) to execute
 * and thus denoting its presence to the WDOG service. Therefore, it's
 * imperative that WDOG monitoring for these tasks be disabled since
 * there is no API to get the IDLE task's WDOG ID. Otherwise, the
 * idle task's monitoring would just be suspended as long as SUOUART
 * was up and running.
 */
#define dg_configWDOG_GUARD_IDLE_TASK            ( 0 )
#endif

/* Include bsp default values */
#include "bsp_defaults.h"
/* Include middleware default values */
#include "middleware_defaults.h"

#endif /* CUSTOM_CONFIG_EFLASH_H_ */
