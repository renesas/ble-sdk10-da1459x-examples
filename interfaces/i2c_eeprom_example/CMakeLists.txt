cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(i2c_eeprom_example)

add_subdirectory(user_app)
target_include_directories(app PRIVATE
	config
)
target_sources(app PRIVATE
	config/platform_devices.c
	main.c
)
