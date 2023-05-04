cmake_minimum_required(VERSION 3.24)
project(Dict2FlashcardsQT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(Boost 1.82 COMPONENTS program_options REQUIRED)

include_directories(src)

option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(src/plugin_wrappers/tests)
endif()

set(SOURCE_FILES src/main.cpp)

add_executable(Dict2FlashcardsQT ${SOURCE_FILES})

target_link_libraries(Dict2FlashcardsQT Boost::program_options)