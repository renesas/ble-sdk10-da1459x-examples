/**
 ****************************************************************************************
 *
 * @file main.c
 *
 * @brief Glucose sensor sample code
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
#include <stdbool.h>
#include "osal.h"
#include "resmgmt.h"
#include "ad_ble.h"
#include "ad_nvms.h"
#include "ad_nvparam.h"
#include "ble_mgr.h"
#include "hw_gpio.h"
#include "sys_clock_mgr.h"
#include "sys_power_mgr.h"
#include "sys_watchdog.h"

#if (dg_configTRACK_OS_HEAP == 1)
/*
 * ConstantsVariables used for Tasks Stack and OS Heap tracking
 * Declared global to avoid IDLE stack Overflows
 */
#define mainMAX_NB_OF_TASKS           10
#define mainMIN_STACK_GUARD_SIZE      8 /* words */
#define mainTOTAL_HEAP_SIZE_GUARD     64 /*bytes */

OS_TASK_STATUS pxTaskStatusArray[mainMAX_NB_OF_TASKS];
#endif /* (dg_configTRACK_OS_HEAP == 1) */
/*
 * Perform any application specific hardware configuration. The clocks,
 * memory, etc. are configured before main() is called.
 */
static void prvSetupHardware( void );

 /*
 * Task functions.
 */
OS_TASK_FUNCTION(glucose_sensor_task, pvParameters);

static OS_TASK_FUNCTION(system_init, pvParameters)
{
        OS_TASK handle;

#if defined CONFIG_RETARGET
        extern void retarget_init(void);
#endif

        /* Use appropriate XTAL for each device */
        cm_sys_clk_init(sysclk_XTAL32M);
        cm_apb_set_clock_divider(apb_div1);
        cm_ahb_set_clock_divider(ahb_div1);
        cm_lp_clk_init();


        /* Prepare the hardware to run this demo. */
        prvSetupHardware();

        /* Set the desired sleep mode */
        pm_set_wakeup_mode(true);
        pm_sleep_mode_set(pm_mode_extended_sleep);

#if defined CONFIG_RETARGET
        retarget_init();
#endif

        /* Initialize BLE Manager */
        ble_mgr_init();

        /* Start the PXP reporter application task */
        OS_TASK_CREATE("Glucose Sensor",                /* The text name assigned to the task, for
                                                           debug only; not used by the kernel. */
                       glucose_sensor_task,             /* The function that implements the task. */
                       NULL,                            /* The parameter passed to the task. */
                       1024,                            /* The number of bytes to allocate to the
                                                           stack of the task. */
                       OS_TASK_PRIORITY_NORMAL,         /* The priority assigned to the task. */
                       handle);                         /* The task handle. */
        OS_ASSERT(handle);

        /* the work of the SysInit task is done */
        OS_TASK_DELETE(OS_GET_CURRENT_TASK());
}

/**
 * @brief BLE FW demo main creates a BLE task
 */
int main( void )
{
        OS_TASK handle;
        OS_BASE_TYPE status __UNUSED;


        /* Start SysInit task. */
        status = OS_TASK_CREATE("SysInit",                /* The text name assigned to the task, for
                                                             debug only; not used by the kernel. */
                                system_init,              /* The System Initialization task. */
                                ( void * ) 0,             /* The parameter passed to the task. */
                                1200,                     /* The number of bytes to allocate to the
                                                             stack of the task. */
                                OS_TASK_PRIORITY_HIGHEST, /* The priority assigned to the task. */
                                handle );                 /* The task handle */
        OS_ASSERT(status == OS_TASK_CREATE_SUCCESS);


        /* Start the tasks and timer running. */
        OS_TASK_SCHEDULER_RUN();

        /* If all is well, the scheduler will now be running, and the following
        line will never be reached.  If the following line does execute, then
        there was insufficient FreeRTOS heap memory available for the idle and/or
        timer tasks to be created.  See the memory management section on the
        FreeRTOS web site for more details. */
        for ( ;; );
}

static void periph_init(void)
{
#if defined CONFIG_RETARGET
#endif


        HW_GPIO_SET_PIN_FUNCTION(LED1);
}

static void prvSetupHardware( void )
{
        /* Init hardware */
        pm_system_init(periph_init);
}

/**
 * @brief Malloc fail hook
 *
 * This function will be called only if it is enabled in the configuration of the OS
 * or in the OS abstraction layer header osal.h, by a relevant macro definition.
 * It is a hook function that will execute when a call to OS_MALLOC() returns error.
 * OS_MALLOC() is called internally by the kernel whenever a task, queue,
 * timer or semaphore is created. It can be also called by the application.
 * The size of the available heap is defined by OS_TOTAL_HEAP_SIZE in osal.h.
 * The OS_GET_FREE_HEAP_SIZE() API function can be used to query the size of
 * free heap space that remains, although it does not provide information on
 * whether the remaining heap is fragmented.
 */
OS_APP_MALLOC_FAILED( void )
{
        ASSERT_ERROR(0);
}

/**
 * @brief Application idle task hook
 *
 * This function will be called only if it is enabled in the configuration of the OS
 * or in the OS abstraction layer header osal.h, by a relevant macro definition.
 * It will be called on each iteration of the idle task.
 * It is essential that code added to this hook function never attempts
 * to block in any way (for example, call OS_QUEUE_GET() with a block time
 * specified, or call OS_TASK_DELAY()). If the application makes use of the
 * OS_TASK_DELETE() API function (as this demo application does) then it is also
 * important that OS_APP_IDLE() is permitted to return to its calling
 * function, because it is the responsibility of the idle task to clean up
 * memory allocated by the kernel to any task that has since been deleted.
 */
OS_APP_IDLE( void )
{
#if (dg_configTRACK_OS_HEAP == 1)
        OS_BASE_TYPE i = 0;
        OS_BASE_TYPE uxMinimumEverFreeHeapSize;

        // Generate raw status information about each task.
        OS_UBASE_TYPE uxNbOfTaskEntries = OS_GET_TASKS_STATUS(pxTaskStatusArray, mainMAX_NB_OF_TASKS);

        for (i = 0; i < uxNbOfTaskEntries; i++) {
                /* Check Free Stack*/
                OS_BASE_TYPE uxStackHighWaterMark;

                uxStackHighWaterMark = OS_GET_TASK_STACK_WATERMARK(pxTaskStatusArray[i].xHandle);
                OS_ASSERT(uxStackHighWaterMark >= mainMIN_STACK_GUARD_SIZE);
        }

        /* Check Minimum Ever Free Heap against defined guard. */
        uxMinimumEverFreeHeapSize = OS_GET_HEAP_WATERMARK();
        OS_ASSERT(uxMinimumEverFreeHeapSize >= mainTOTAL_HEAP_SIZE_GUARD);
#endif /* (dg_configTRACK_OS_HEAP == 1) */

#if dg_configUSE_WDOG
        sys_watchdog_idle_task_notify();
#endif
}

/**
 * @brief Application stack overflow hook
 *
 * Run-time stack overflow checking is performed only if it is enabled in the configuration of the OS
 * or in the OS abstraction layer header osal.h, by a relevant macro definition.
 * This hook function is called if a stack overflow is detected.
 */
OS_APP_STACK_OVERFLOW( OS_TASK pxTask, char *pcTaskName )
{
        ( void ) pcTaskName;
        ( void ) pxTask;

        ASSERT_ERROR(0);
}

/**
 * @brief Application tick hook
 *
 * This function will be called only if it is enabled in the configuration of the OS
 * or in the OS abstraction layer header osal.h, by a relevant macro definition.
 * This hook function is executed each time a tick interrupt occurs.
 */
OS_APP_TICK( void )
{
}
