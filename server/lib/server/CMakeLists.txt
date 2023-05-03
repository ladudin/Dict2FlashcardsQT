add_library(plugin_server server.cpp)
target_link_libraries(plugin_server serverside_plugin_wrappers)
target_include_directories(plugin_server PUBLIC ./)
