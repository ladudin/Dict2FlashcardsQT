cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# set(CMAKE_AUTOMOC_MOC_OPTIONS "moc=/usr/lib/x86_64-linux-gnu/qt5/bin")

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
# find_package(Qt5Network REQUIRED)
find_package(Qt5Multimedia REQUIRED)
FIND_PACKAGE( Qt5MultimediaWidgets REQUIRED )

SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

add_executable(qt 
main.cpp
AudioPlayer.cpp
AudioWidget.cpp
deck_model.cpp
ExamplesWidget.cpp
ImagesWidget.cpp
mainwindow.cpp
word_cards.cpp
main.cpp
AudioPlayer.ui
AudioWidget.ui
ExamplesWidget.ui
ImagesWidget.ui
mainwindow.ui
Deck.cpp
)
target_include_directories(qt PUBLIC ./)

target_link_libraries(qt 
Qt${QT_VERSION_MAJOR}::Widgets
Qt5::Multimedia
Qt5::Network
media
connection
definitions_provider_wrapper
definitions_provider_interface
format_processor_plugin_wrapper
card
word_plugin_wrapper
)

QT5_USE_MODULES (qt Multimedia MultimediaWidgets)