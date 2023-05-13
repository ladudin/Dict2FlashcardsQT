add_library(plugins_loader plugins_loader.cpp)
target_include_directories(plugins_loader PUBLIC
    ./
    PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(plugins_loader
    containers
    definitions_provider_wrapper
    images_provider_wrapper
    sentences_provider_wrapper
    audios_provider_wrapper
    format_processor_wrapper
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
