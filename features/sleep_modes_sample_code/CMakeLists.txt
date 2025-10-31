cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(sleep_modes_sample_code)

add_subdirectory(src)
target_include_directories(app PRIVATE
	misc
	config
)
target_sources(app PRIVATE
	main.c
)
