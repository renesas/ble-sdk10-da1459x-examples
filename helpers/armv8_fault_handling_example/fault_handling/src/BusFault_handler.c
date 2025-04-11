/**
 ****************************************************************************************
 *
 * @file BusFault_handler.c
 *
 * Copyright (C) 2015-2023 Renesas Electronics Corporation and/or its affiliates
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

#include <stdio.h>
#include <stdbool.h>
#include "hw_cpm.h"
#include "hw_watchdog.h"
#include "fault_handling.h"
#include "user_application.h"

extern volatile Fault_t _fault_exception_info __UNUSED;
extern volatile bool fault_escalation_flag;

#if (FAULT_HANDLING_MODE == 1)
        /* Just for debugging purposes to avoid optimizing symbols */
        __UNUSED volatile uint32_t dbg_fp_context;
        __UNUSED volatile uint32_t *dbg_fault_args;
#endif

/*
 * User-defined BusFault handler. This is the 2nd part of the handler written in
 * C language. Depending on the handling mode the stacked frame can either
 * be exercised instantly by attaching a debugger or the stacked frame info
 * is stored in dedicated area and device reboots. At the next boot cycle the
 * stored stacked frame can be exercised by calling system_boot_status_check_and_analyze.
 */
__ALWAYS_RETAINED_CODE
void BusFault_HandlerC(uint32_t *fault_args, uint32_t fp_context)
{
#if dg_configENABLE_MTB
        /* Disable MTB */
        *MTB_MASTER_REG = MTB_MASTER_REG_DISABLE_VAL;
#endif

        /*
         * If set, trigger a fault either of the same or different type with
         * the same or lower priority so that for the new fault exception to
         * be escalated to HardFault.
         */
        if (fault_escalation_flag) {
                /* Perform an unaligned memory access */
                volatile uint32_t *ptr = (volatile uint32_t *)0x50030E01;
                *ptr = 0xFFFFFFFF;
        }

        hw_watchdog_freeze(); // Freeze WDOG

#if (FAULT_HANDLING_MODE == 1)

        ENABLE_DEBUGGER;

        dbg_fp_context = fp_context;
        dbg_fault_args = fault_args;

        /* BusFault Address Register (BFAR) */
        __UNUSED volatile uint32_t bus_fault_addr = 0;
        /* BusFault Status Register (BFSR) */
        __UNUSED volatile uint8_t bus_fault_status = _FLD2VAL(SCB_CFSR_BUSFAULTSR, SCB->CFSR);

        /*
         * Check if BusFault Address Register (BFAR) contains a valid address.
         *
         * Bits  Name         Description
         * [7]   BFARVALID    Indicates if BFAR contains a valid fault address.
         *
         * If BFARVALID == 0:
         *      - An imprecise fault exception tool place, that is, the exception was not triggered immediately as it might
         *        happen that a bus transaction was buffered.
         *      - The fault took place during stacking/unstacking process.
         *
         */
        if (bus_fault_status & 0x80) {
                bus_fault_addr = SCB->BFAR;
        }

        /*
         *  Stacked Core Registers:
         *
         * - fault_args[0] --> R0
         * - fault_args[1] --> R1
         * - fault_args[2] --> R2
         * - fault_args[3] --> R3
         * - fault_args[4] --> R12
         * - fault_args[5] --> LR
         * - fault_args[6] --> PC
         * - fault_args[7] --> xPSR
         *
         * if fp_context > 0:
         *      - fault_args[8..23] --> S[0..15]
         *      - fault_args[24] --> FPSCR
         * else:
         *      - fault_args[8..24] --> invalid
         *
         */

        /* Check if debugger is already attached and halt CPU operation */
        if (REG_GETF(CRG_TOP, SYS_STAT_REG, DBG_IS_ACTIVE)) {
                __BKPT(0);
        } else {
                /* Otherwise, turn on LED1 and wait forever. */
                turn_on_led1();

                while (1) {}
        }

#elif (FAULT_HANDLING_MODE == 2)

        _fault_exception_info.magic_val = FAULT_HANDLING_MAGIC_VALUE;
        _fault_exception_info.irq_num   = __get_IPSR();

        _fault_exception_info._r0   = fault_args[0];
        _fault_exception_info._r1   = fault_args[1];
        _fault_exception_info._r2   = fault_args[2];
        _fault_exception_info._r3   = fault_args[3];
        _fault_exception_info._r12  = fault_args[4];
        _fault_exception_info._lr   = fault_args[5];
        _fault_exception_info._pc   = fault_args[6];
        _fault_exception_info._xPSR = fault_args[7];


        if (fp_context == 0) {
                _fault_exception_info.is_fp_valid = false;

                for (int i = 0; i < STACKED_FRAME_FP_MAX_ENTRIES; i++) {
                        *((uint32_t *)&_fault_exception_info._s0 + (i * 4)) = 0UL;
                }

        } else {
                _fault_exception_info.is_fp_valid = true;

                for (int i = 0; i < STACKED_FRAME_FP_MAX_ENTRIES; i++) {
                        *((uint32_t *)&_fault_exception_info._s0 + (i * 4)) = fault_args[i + STACKED_FRAME_FP_IDX_START];
                }
        }

        _fault_exception_info._CFSR._CFSR = SCB->CFSR;
        _fault_exception_info._HFSR  = SCB->HFSR;
        _fault_exception_info._DFSR  = SCB->DFSR;
        _fault_exception_info._AFSR  = SCB->AFSR;
        _fault_exception_info._MMFAR = SCB->MMFAR;
        _fault_exception_info._BFAR  = SCB->BFAR;

        hw_cpm_reboot_system();

        /* Wait for WDOG to expire and reset the device. */
        while (1) {}

#endif /* FAULT_HANDLING_MODE */
}
