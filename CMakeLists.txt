cmake_minimum_required(VERSION 3.24)
project(Dict2FlashcardsQT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(Boost 1.82 COMPONENTS program_options REQUIRED)

enable_testing()
find_package(GTest REQUIRED)

set(SOURCE_FILES src/main.cpp)

add_subdirectory(client)

add_executable(Dict2FlashcardsQT ${SOURCE_FILES})

target_link_libraries(Dict2FlashcardsQT
        connection
        word_plugin_wrapper
        audio_plugin_wrapper
        image_plugin_wrapper
        sentence_plugin_wrapper
        format_processor_plugin_wrapper)