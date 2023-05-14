cmake_minimum_required(VERSION 3.24)
project(Dict2FlashcardsQT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(Boost 1.82 COMPONENTS program_options REQUIRED)
#find_package(nlohmann_json 3.11.2 REQUIRED)
#
#find_package(GTest REQUIRED)
#
#target_link_libraries(tests GTest::gtest_main)

set(SOURCE_FILES src/main.cpp)

add_subdirectory(lib/client/connection)
add_subdirectory(lib/client/plugin_wrappers)

add_executable(Dict2FlashcardsQT ${SOURCE_FILES})

target_link_libraries(Dict2FlashcardsQT client_plugin_wrappers)