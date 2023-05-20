cmake_minimum_required(VERSION 3.22)

project(Dict2FlashcardsQT)
set(CMAKE_CXX_STANDARD 20)

# Copyright(c) 2019 spdlog authors Distributed under the MIT License (http://opensource.org/licenses/MIT)
cmake_minimum_required(VERSION 3.10)
project(spdlog_examples CXX)

# Logger
add_subdirectory(spdlog)
link_libraries(spdlog::spdlog_header_only)

add_subdirectory(server)

add_subdirectory(test_client)
add_subdirectory(python_tests)
