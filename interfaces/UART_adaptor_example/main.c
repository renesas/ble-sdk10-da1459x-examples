#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "peripheral_setup.h"
#include "platform_devices.h"
#include "osal.h"
#include "resmgmt.h"
#include "hw_cpm.h"
#include "hw_gpio.h"
#include "hw_watchdog.h"
#include "sys_clock_mgr.h"
#include "sys_power_mgr.h"
#include "hw_pdc.h"
#include "ad_spi.h"
#include "hw_wkup.h"
#include "hw_sys.h"
#include "sys_watchdog.h"

#if (DBG_PRINT_ENABLE == 1)
# define DBG_PRINTF(_f, args...)   printf((_f), ## args)
#else
# define DBG_PRINTF(_f, args...)
#endif

/* Task function declarations */
OS_TASK_FUNCTION(prv_Uart1_echo_Task, pvParameters);
OS_TASK_FUNCTION(prv_Uart2_async_RX_Task, pvParameters);
OS_TASK_FUNCTION(prv_Uart2_async_TX_Task, pvParameters);

/* Task priorities */
#define UART1_TASK_PRIORITY            OS_TASK_PRIORITY_NORMAL
#define UART2_TASK_PRIORITY            (OS_TASK_PRIORITY_NORMAL + 1) // Higher priority to UART2

/* Define task handles */
static OS_TASK uart2_rx_task_h = NULL;
static OS_TASK uart2_tx_task_h = NULL;
static OS_TASK uart1_echo_task_h = NULL;

/* Queue for transferring characters between UART2 RX and TX tasks */
#define UART2_QUEUE_LENGTH             10
#define UART2_ITEM_SIZE                sizeof(char)
static OS_QUEUE uart2_queue_h;

/* Function to set up hardware configuration */
static void prvSetupHardware(void);

/* Initialize system and create tasks */
static OS_TASK_FUNCTION(system_init, pvParameters)
{
    OS_TASK_BEGIN();

    /* Initialize system clock and power */
    cm_sys_clk_init(sysclk_XTAL32M);
    cm_apb_set_clock_divider(apb_div1);
    cm_ahb_set_clock_divider(ahb_div1);
    cm_lp_clk_init();

    /* Initialize hardware */
    prvSetupHardware();

    /* Set desired power mode */
    pm_set_wakeup_mode(true);
    pm_sleep_mode_set(pm_mode_extended_sleep);

    /* Create UART2 queue */
    OS_QUEUE_CREATE(uart2_queue_h, UART2_ITEM_SIZE, UART2_QUEUE_LENGTH);
    OS_ASSERT(uart2_queue_h != NULL);

    /* Create UART1 Echo Task (Lower Priority Group) */
    OS_TASK_CREATE("UART1 Echo", prv_Uart1_echo_Task, NULL, configMINIMAL_STACK_SIZE * OS_STACK_WORD_SIZE,
                   UART1_TASK_PRIORITY, uart1_echo_task_h);
    OS_ASSERT(uart1_echo_task_h);

    /* Create UART2 RX Task with RTS/CTS Flow Control (Higher Priority Group) */
    OS_TASK_CREATE("UART2 RX", prv_Uart2_async_RX_Task, NULL, configMINIMAL_STACK_SIZE * OS_STACK_WORD_SIZE,
                   UART2_TASK_PRIORITY, uart2_rx_task_h);
    OS_ASSERT(uart2_rx_task_h);

    /* Create UART2 TX Task with RTS/CTS Flow Control (Higher Priority Group) */
    OS_TASK_CREATE("UART2 TX", prv_Uart2_async_TX_Task, NULL, configMINIMAL_STACK_SIZE * OS_STACK_WORD_SIZE,
                   UART2_TASK_PRIORITY, uart2_tx_task_h);
    OS_ASSERT(uart2_tx_task_h);

    /* Suspend UART2 tasks initially */
    OS_TASK_SUSPEND(uart2_rx_task_h);
    OS_TASK_SUSPEND(uart2_tx_task_h);

    /* Delete system initialization task */
    OS_TASK_DELETE(OS_GET_CURRENT_TASK());
}


/**
 * @brief Main function initializes system and starts scheduler
 */
int main(void)
{
    OS_TASK handle;
    OS_BASE_TYPE status __UNUSED;

    /* Create System Initialization task */
    status = OS_TASK_CREATE("SysInit", system_init, (void *)0, 1200,
                            OS_TASK_PRIORITY_HIGHEST, handle);
    OS_ASSERT(status == OS_TASK_CREATE_SUCCESS);

    /* Start task scheduler */
    OS_TASK_SCHEDULER_RUN();

    for (;;);
}

/**
 * UART1 Echo Task - UART1 tasks run independently and then yield control to UART2 tasks.
 */
OS_TASK_FUNCTION(prv_Uart1_echo_Task, pvParameters)
{
    OS_TASK_BEGIN();
    char c = 0;
    uint32_t bytes;
    ad_uart_handle_t uart1_h;

    uart1_h = ad_uart_open(&uart1_uart_conf);
    ASSERT_ERROR(uart1_h != NULL);

    const char *test_message = "UART1 Echo Test. Type to echo back:\r\n";
    ad_uart_write(uart1_h, test_message, strlen(test_message));

    do {
        bytes = ad_uart_read(uart1_h, &c, 1, OS_EVENT_FOREVER);
        if (bytes > 0) {
            ad_uart_write(uart1_h, &c, bytes);
            DBG_PRINTF("Echoed character: %c\n", c);
        }
    } while (c != 27);

    /* Switch to UART2 tasks once UART1 task finishes */
    OS_TASK_RESUME(uart2_rx_task_h);
    OS_TASK_RESUME(uart2_tx_task_h);
    OS_TASK_SUSPEND(uart1_echo_task_h);

    while (ad_uart_close(uart1_h, false) == AD_UART_ERROR_CONTROLLER_BUSY);
    OS_TASK_DELETE(OS_GET_CURRENT_TASK());
    OS_TASK_END();
}

/**
 * UART2 RX Task with RTS/CTS Flow Control - Higher priority, runs after UART1 Echo Task is done.
 */
OS_TASK_FUNCTION(prv_Uart2_async_RX_Task, pvParameters)
{
    OS_TASK_BEGIN();
    char c;
    uint32_t bytes;
    ad_uart_handle_t uart2_h;

    uart2_h = ad_uart_open(&uart2_uart_conf);
    ASSERT_ERROR(uart2_h != NULL);

    const char *rx_message = "UART2 RX with RTS/CTS Flow Control. Awaiting input:\r\n";
    ad_uart_write(uart2_h, rx_message, strlen(rx_message));

    do {
        bytes = ad_uart_read(uart2_h, &c, 1, OS_EVENT_FOREVER);
        if (bytes > 0) {
            DBG_PRINTF("UART2 Received: %c\n", c);
            /* Send received character to TX task for echoing */
            OS_QUEUE_PUT(uart2_queue_h, &c, OS_QUEUE_FOREVER);
        }
    } while (c != 27);

    while (ad_uart_close(uart2_h, false) == AD_UART_ERROR_CONTROLLER_BUSY);
    OS_TASK_DELETE(OS_GET_CURRENT_TASK());
    OS_TASK_END();
}

/**
 * UART2 TX Task with RTS/CTS Flow Control - Higher priority, runs after UART1 Echo Task is done.
 */
OS_TASK_FUNCTION(prv_Uart2_async_TX_Task, pvParameters)
{
    OS_TASK_BEGIN();
    char c;
    ad_uart_handle_t uart2_h;

    uart2_h = ad_uart_open(&uart2_uart_conf);
    ASSERT_ERROR(uart2_h != NULL);

    const char *tx_message = "Sending message from UART2 TX with RTS/CTS.\r\n";
    ad_uart_write(uart2_h, tx_message, strlen(tx_message));

    while (1) {
        /* Receive character from RX task and send it back to UART */
        if (OS_QUEUE_GET(uart2_queue_h, &c, OS_QUEUE_FOREVER) == OS_OK) {
            ad_uart_write(uart2_h, &c, 1);
            DBG_PRINTF("UART2 Echoed character: %c\n", c);
        }
    }

    while (ad_uart_close(uart2_h, false) == AD_UART_ERROR_CONTROLLER_BUSY);
    OS_TASK_DELETE(OS_GET_CURRENT_TASK());
    OS_TASK_END();
}

/* Peripheral initialization */
static void periph_init(void) { }

/* Hardware setup function */
static void prvSetupHardware(void)
{
    pm_system_init(periph_init);
}

/* OS Hooks */
void vApplicationMallocFailedHook(void) { for (;;) {} }
void vApplicationIdleHook(void) { sys_watchdog_idle_task_notify(); }
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) { for (;;) {} }
