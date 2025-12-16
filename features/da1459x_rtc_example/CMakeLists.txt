cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(da1459x_rtc_example)

add_subdirectory(rtc)
target_sources(app PRIVATE
	main.c
	rtc_demo_task.c
)
