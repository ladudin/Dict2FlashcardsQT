# set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
FIND_PACKAGE( Qt5MultimediaWidgets REQUIRED )

SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)

add_library(audio_player 
AudioPlayer.cpp 
# AudioPlayer.hpp 
AudioPlayer.ui 
)

target_include_directories(audio_player PUBLIC ./)

target_link_libraries(audio_player
Qt5::Widgets
Qt5::Multimedia
# Qt5::Network
card
)

QT5_USE_MODULES (audio_player Multimedia MultimediaWidgets)