cmake_minimum_required(VERSION 3.20.0)

set(CONFIG_USE_BLE ON)
set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(dsps_ble_central)

add_subdirectory(misc)
add_subdirectory(dsps)
target_include_directories(app PRIVATE config)
target_sources(app PRIVATE
	config/platform_devices.c
	dsps_ble_central_task.c
	main.c
)
