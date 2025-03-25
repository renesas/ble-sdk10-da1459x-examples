/**
 ****************************************************************************************
 *
 * @file platform_devices.h
 *
 * @brief Configuration of devices connected to board.
 *
 * Copyright (C) 2016-2025 Renesas Electronics Corporation and/or its affiliates.
 * This computer program includes Confidential, Proprietary Information
 * of Renesas Electronics Corporation and/or its affiliates. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef PLATFORM_DEVICES_H_
#define PLATFORM_DEVICES_H_

#include "hw_timer.h"

extern timer_config app_timer_cfg;

#define APP_TIMER_DEVICE  (&app_timer_cfg)

#endif /* PLATFORM_DEVICES_H_ */
