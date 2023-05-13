add_library(plugins_bundle plugins_bundle.cpp)
target_link_libraries(plugins_bundle
    definitions_provider_wrapper
    images_provider_wrapper
    sentences_provider_wrapper
    audios_provider_wrapper
    format_processor_wrapper
)
target_include_directories(plugins_bundle PUBLIC ./)
