add_subdirectory(lib)

add_executable(server_main main.cpp)
target_link_libraries(server_main plugin_server)
