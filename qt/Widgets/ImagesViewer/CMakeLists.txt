# set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

add_library(images_viewer
ImagesWidget.cpp 
# ImagesWidget.hpp 
ImagesWidget.ui
)

target_include_directories(images_viewer PUBLIC ./)

target_link_libraries(images_viewer
Qt5::Widgets
Qt5::Network
card
)