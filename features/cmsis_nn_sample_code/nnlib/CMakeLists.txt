target_include_directories(app PRIVATE Include)
target_link_libraries(app PRIVATE "${CMAKE_CURRENT_LIST_DIR}/libcmsis-nn.a")
