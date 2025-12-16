cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(cmsis_nn_sample_code)

add_subdirectory(nnlib)
target_include_directories(app PRIVATE test-includes)
target_sources(app PRIVATE
	main.c
	test_arm_convolve_fast_s16.c
	test_arm_fully_connected_s16.c
)
