add_library(sentences_provider_wrapper SentencesProviderWrapper.cpp)
target_include_directories(sentences_provider_wrapper PUBLIC ./)
target_link_libraries(sentences_provider_wrapper base_plugin_wrapper base_container)

# set(serverside_plugin_wrappers
#     "${serverside_plugin_wrappers} sentences_provider_wrapper"
#     PARENT_SCOPE)
