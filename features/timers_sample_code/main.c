/**
 ****************************************************************************************
 *
 * @file main.c
 *
 * @brief HW timer demonstration example
 *
 * Copyright (C) 2015-2025 Renesas Electronics Corporation and/or its affiliates.
 * This computer program includes Confidential, Proprietary Information
 * of Renesas Electronics Corporation and/or its affiliates. All Rights Reserved.
 *
 ****************************************************************************************
 */
#include <stdbool.h>
#include "osal.h"
#include "hw_gpio.h"
#include "sys_clock_mgr.h"
#include "sys_power_mgr.h"
#include "sys_watchdog.h"
#include "hw_sys.h"
#include "platform_devices.h"
#include "periph_setup.h"

/*
 * Perform any application specific hardware configuration.  The clocks,
 * memory, etc. are configured before main() is called.
 */
static void prvSetupHardware( void );

/*
 * Task functions .
 */
OS_TASK_FUNCTION(app_timer_task, pvParameters);

/**
 * @brief system_init() initialize the system
 */
static OS_TASK_FUNCTION(system_init, pvParameters)
{
        OS_TASK handle;
        OS_BASE_TYPE status;

#if defined CONFIG_RETARGET
        extern void retarget_init(void);
#endif

        cm_sys_clk_init(sysclk_XTAL32M);

        cm_apb_set_clock_divider(apb_div1);
        cm_ahb_set_clock_divider(ahb_div1);
        cm_lp_clk_init();

        /* Prepare the hardware to run this demo. */
        prvSetupHardware();

#if defined CONFIG_RETARGET
        retarget_init();
#endif

        /* true - wait for the XTAL32M to settle before running any OS task on wake-up */
        pm_set_wakeup_mode(true);

        /*
         * PDC cannot be triggered following event on the capture channels and so the sleep
         * mode cannot be used.
         */
        pm_sleep_mode_set(APP_TIMER_CAPTURE_EN ? pm_mode_idle : pm_mode_extended_sleep);

        status = OS_TASK_CREATE("APP_TIMER",                            /* The text name assigned to the task, for
                                                                           debug only; not used by the kernel. */
                        app_timer_task,                                 /* The System Initialization task. */
                        ( void * ) 0,                                   /* The parameter passed to the task. */
                        1024,                                           /* The number of bytes to allocate to the
                                                                           stack of the task. */
                        OS_TASK_PRIORITY_NORMAL,                        /* The priority assigned to the task.
                                                                           we need this task to run first with
                                                                           no interruption, that is why choose
                                                                           HIGHEST priority*/
                        handle );                                       /* The task handle */
        OS_ASSERT(status == OS_TASK_CREATE_SUCCESS);                    /* Check that the task created OK */

        /* the work of the SysInit task is done
         * The task will be terminated */
        OS_TASK_DELETE( OS_GET_CURRENT_TASK() );
}

/**
 * @brief Template main creates a SysInit task, which creates a Template task
 */
int main( void )
{
        OS_BASE_TYPE status;
        OS_TASK xHandle;

        /* Start the two tasks as described in the comments at the top of this
        file. */
        status = OS_TASK_CREATE("SysInit",              /* The text name assigned to the task, for
                                                           debug only; not used by the kernel. */
                        system_init,                    /* The System Initialization task. */
                        ( void * ) 0,                   /* The parameter passed to the task. */
                        configMINIMAL_STACK_SIZE * OS_STACK_WORD_SIZE,
                                                        /* The number of bytes to allocate to the
                                                           stack of the task. */
                        OS_TASK_PRIORITY_HIGHEST,       /* The priority assigned to the task. */
                        xHandle );                      /* The task handle */
        OS_ASSERT(status == OS_TASK_CREATE_SUCCESS);



        /* Start the tasks and timer running. */
        vTaskStartScheduler();

        /* If all is well, the scheduler will now be running, and the following
        line will never be reached.  If the following line does execute, then
        there was insufficient FreeRTOS heap memory available for the idle and/or
        timer tasks to be created.  See the memory management section on the
        FreeRTOS web site for more details. */
        for ( ;; );

}


/**
 * @brief Initialize the peripherals domain after power-up.
 *
 */
static void periph_init(void)
{
        /*
         * Recommended place to support GPIO not controlled directly by some kind of adapter.
         * Keep in mind that this routine is called every time the device exits the extended
         * sleep state and before the OS scheduler executes again. Typical case is to configure
         * the mode, functionality and state of a pin.
         */
}

/**
 * @brief Hardware Initialization
 */
static void prvSetupHardware( void )
{
        /* Init hardware */
        pm_system_init(periph_init);

        /* Recommended place to configure I/O pins (controlled by adapters) in the OFF state. */

#if !dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE
        /* GPIO controller resides in PD_COM and so it should be enabled before accessing any GPIO. */
        hw_sys_pd_com_enable();
#endif

#if APP_TIMER_CAPTURE_EN
        /* Setup the pin/port used for capturing events */
        if (APP_TIMER_CAPTURE_PORT != HW_TIMER_GPIO_GPIO_NONE) {
                HW_GPIO_PORT port =
                        APP_TIMER_CAPTURE_PORT >= HW_TIMER_GPIO_PIN_P1_0 ?
                                HW_GPIO_PORT_1 : HW_GPIO_PORT_0;
                HW_GPIO_PIN pin =
                        APP_TIMER_CAPTURE_PORT >= HW_TIMER_GPIO_PIN_P1_0 ?
                                APP_TIMER_CAPTURE_PORT - HW_TIMER_GPIO_PIN_P1_0 :
                                APP_TIMER_CAPTURE_PORT - 1;
                hw_gpio_set_pin_function(port, pin, HW_GPIO_MODE_INPUT, HW_GPIO_FUNC_GPIO);
                hw_gpio_pad_latch_enable(port, pin);
                hw_gpio_pad_latch_disable(port, pin);
        }
#endif

#if !dg_configPM_ENABLES_PD_COM_WHILE_ACTIVE
        /* When PD_COM is not needed it should be disabled to minimize power consumption when in the sleep state. */
        hw_sys_pd_com_disable();
#endif
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
        /* Needed if the idle task is configured to be tracked by the system WDG service. */
        sys_watchdog_idle_task_notify();
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
