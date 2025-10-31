cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(armv8_fault_handling_example)

add_subdirectory(fault_handling)
target_include_directories(app PRIVATE
	config
	misc
)
target_sources(app PRIVATE
	fault_handling_task.c
	main.c
)
