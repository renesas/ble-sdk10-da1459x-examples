/**
 ****************************************************************************************
 *
 * @file user_application.h
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

#ifndef USER_APPLICATION_H_
#define USER_APPLICATION_H_

#include <stdbool.h>

/*
 * There are flavors for handling fault exceptions:
 *
 * 1 --> CPU execution is trapped and/or handled waiting for the user to attach a debugger
 *       and perform a debugging session.
 *
 * 2 --> System's state is stored in a dedicated area in SRAM and a HW reset is triggered
 *       for the system to recover. Upon next boot the stored info is exercised and various
 *       debug info is printed on the console (if enabled). Please note that this mode is
 *       invalid when images are built for RAM execution. This is because RAM images require
 *       that debugger be attached and so rebooting the device is not allowed.
 *
 **/
#ifndef FAULT_HANDLING_MODE
#define FAULT_HANDLING_MODE           ( 1 )
#endif

/*
 * It should be called at the beginning of the application (e.g. inside application tasks)
 * to check if system booted normally or because of a fault exception.
 */
void system_boot_status_check_and_analyze(void);

/* If set an escalated fault will be triggered on purposed inside BusFault handler to demonstrate
 * the ARM exception escalation mechanism. */
void fault_escalation_status_set(bool status);

#endif /* USER_APPLICATION_H_ */
