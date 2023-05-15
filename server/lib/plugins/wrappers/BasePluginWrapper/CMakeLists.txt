add_library(base_plugin_wrapper INTERFACE)
target_include_directories(base_plugin_wrapper INTERFACE ./)
target_link_libraries(base_plugin_wrapper INTERFACE
    plugin_wrapper_interface
)
