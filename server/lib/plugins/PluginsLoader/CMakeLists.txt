message(${CMAKE_CURRENT_SOURCE_DIR})

add_library(plugins_loader INTERFACE)
target_include_directories(plugins_loader INTERFACE
    ./
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(plugins_loader
    INTERFACE
    # containers
    py_exception_info
    definitions_provider_wrapper
    images_provider_wrapper
    sentences_provider_wrapper
    audios_provider_wrapper
    format_processor_wrapper
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)
