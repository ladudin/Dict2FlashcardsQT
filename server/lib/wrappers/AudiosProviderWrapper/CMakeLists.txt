add_library(audios_provider_wrapper audios_provider_wrapper.cpp)
target_include_directories(audios_provider_wrapper PUBLIC ./)
target_link_libraries(audios_provider_wrapper plugin_wrapper_interface)

set(serverside_plugin_wrappers
    "${serverside_plugin_wrappers} audios_provider_wrapper"
    PARENT_SCOPE)
