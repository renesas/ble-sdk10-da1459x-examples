cmake_minimum_required(VERSION 3.20.0)

set(CONFIG_USE_BLE ON)
set(SDK10_INCLUDE_DIRECTORIES config)
set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(glucose_sensor_sample_code)

add_subdirectory(src)
add_subdirectory(gls)
target_include_directories(app PRIVATE misc)
