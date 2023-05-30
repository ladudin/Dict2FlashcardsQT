# set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


set(PROJECT_SOURCES
    ExamplesWidget.cpp 
    ExamplesWidget.hpp 
    ExamplesWidget.ui
)

add_library(examples_viewer ${PROJECT_SOURCES})

target_include_directories(examples_viewer PUBLIC ./)

target_link_libraries(examples_viewer 
Qt5::Widgets
)
