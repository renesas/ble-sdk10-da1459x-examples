cmake_minimum_required(VERSION 3.20.0)

set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(timers_sample_code)

target_include_directories(app PRIVATE
	config
	misc
)
target_sources(app PRIVATE
	config/platform_devices.c
	main.c
	timer_pwm.c
)
