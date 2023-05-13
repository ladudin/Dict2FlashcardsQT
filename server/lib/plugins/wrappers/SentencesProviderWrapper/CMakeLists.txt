add_library(sentences_provider_wrapper sentences_provider_wrapper.cpp)
target_include_directories(sentences_provider_wrapper PUBLIC ./)
target_link_libraries(sentences_provider_wrapper plugin_wrapper_interface)

# set(serverside_plugin_wrappers
#     "${serverside_plugin_wrappers} sentences_provider_wrapper"
#     PARENT_SCOPE)
