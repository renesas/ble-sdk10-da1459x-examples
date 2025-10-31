target_include_directories(app PRIVATE include)
target_compile_definitions(app PRIVATE ARM_MATH_ARMV8MML)
target_link_libraries(app PRIVATE "${CMAKE_CURRENT_LIST_DIR}/libarm_ARMv8MMLldfsp_math.a")
