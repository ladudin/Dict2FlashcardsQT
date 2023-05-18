cmake_minimum_required(VERSION 3.24)
project(Dict2FlashcardsQT)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(Boost 1.82 COMPONENTS program_options REQUIRED)

enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(client)

add_executable(Dict2FlashcardsQT src/main.cpp)
target_link_libraries(Dict2FlashcardsQT card)