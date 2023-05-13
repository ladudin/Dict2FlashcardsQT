add_library(format_processor_wrapper format_processor_wrapper.cpp)
target_include_directories(format_processor_wrapper PUBLIC ./)
target_link_libraries(format_processor_wrapper plugin_wrapper_interface)

# set(serverside_plugin_wrappers
#     "${serverside_plugin_wrappers} format_processor_wrapper"
#     PARENT_SCOPE)
