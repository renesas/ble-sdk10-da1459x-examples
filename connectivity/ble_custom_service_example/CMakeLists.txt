cmake_minimum_required(VERSION 3.20.0)

set(CONFIG_USE_BLE ON)
set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(ble-attribute-example)

add_subdirectory(custom_service_framework)
target_include_directories(app PRIVATE misc)
target_sources(app PRIVATE
	main.c
	ble_peripheral_task.c
)
