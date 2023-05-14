cmake_minimum_required(VERSION 3.24)
project(Dict2FlashcardsQT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(Boost 1.82 COMPONENTS program_options REQUIRED)
#find_package(nlohmann_json 3.11.2 REQUIRED)

include_directories(src)

find_package(GTest REQUIRED)

#include(CTest)
#enable_testing()

set(TEST_FILES src/plugin_wrappers/basic_plugin_wrapper/BasicPluginWrapper.cpp
        src/plugin_wrappers/tests/src/BasicPluginWrapper_tests.cpp)
add_executable(tests ${TEST_FILES})
target_link_libraries(tests GTest::gtest_main)
#
#add_test(tests tests)

set(SOURCE_FILES src/main.cpp
        src/data_providers/server_connection/ServerConnection.cpp
        src/plugin_wrappers/plugin_wrapper_interfaces/IBasicPluginWrapper.h
        src/plugin_wrappers/basic_plugin_wrapper/BasicPluginWrapper.cpp
        src/plugin_wrappers/word_plugin_wrapper/WordPluginWrapper.cpp)

add_executable(Dict2FlashcardsQT ${SOURCE_FILES})

#target_link_libraries(Dict2FlashcardsQT Boost::program_options PRIVATE nlohmann_json::nlohmann_json)