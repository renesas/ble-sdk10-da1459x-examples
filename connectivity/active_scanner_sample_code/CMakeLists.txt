cmake_minimum_required(VERSION 3.20.0)

set(CONFIG_USE_BLE ON)
set(SDK10_INCLUDE_FILES config/custom_config_eflash.h)

find_package(SDK10 REQUIRED)

project(active_scanner_sample_code)

target_include_directories(app PRIVATE misc)
add_subdirectory(src)
