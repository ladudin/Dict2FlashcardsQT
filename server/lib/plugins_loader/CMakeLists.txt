add_library(plugins_loader plugins_loader.cpp)
target_include_directories(plugins_loader PUBLIC ./)
target_link_libraries(plugins_loader
    serverside_plugin_wrappers
    containers)
