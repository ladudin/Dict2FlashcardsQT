add_library(images_provider_wrapper ImagesProviderWrapper.cpp)
target_include_directories(images_provider_wrapper PUBLIC ./)
target_link_libraries(images_provider_wrapper plugin_wrapper_interface)
#
# set(serverside_plugin_wrappers
#     "${serverside_plugin_wrappers} images_provider_wrapper"
#     PARENT_SCOPE)
