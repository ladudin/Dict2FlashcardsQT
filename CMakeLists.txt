cmake_minimum_required(VERSION 3.22)

project(Dict2FlashcardsQT)
set(CMAKE_CXX_STANDARD 20)

# Copyright(c) 2019 spdlog authors Distributed under the MIT License (http://opensource.org/licenses/MIT)
cmake_minimum_required(VERSION 3.10)
project(spdlog_examples CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# Logger
add_subdirectory(spdlog)
link_libraries(spdlog::spdlog_header_only)
add_subdirectory(server)
