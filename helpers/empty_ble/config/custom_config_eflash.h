#pragma once

#include "bsp_definitions.h"

#define CONFIG_USE_BLE

#define dg_configEXEC_MODE MODE_IS_CACHED
#define dg_configCODE_LOCATION NON_VOLATILE_IS_EMBEDDED_FLASH

#define OS_FREERTOS
#define configTOTAL_HEAP_SIZE 15852

#include "bsp_defaults.h"
#include "middleware_defaults.h"
