cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(cmsis_dsp_sample_code)

add_subdirectory(dsplib)
target_sources(app PRIVATE
	arm_sin_cos_example_f32.c
	main.c
)
