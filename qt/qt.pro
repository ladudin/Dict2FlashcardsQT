QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiolinks.cpp \
    deck.cpp \
    deck_model.cpp \
    deckmock.cpp \
    examples_model.cpp \
    image_links.cpp \
    main.cpp \
    mainwindow.cpp \
    word_cards.cpp

HEADERS += \
    IDeck.h \
    audiolinks.h \
    card.h \
    deck.h \
    deck_model.h \
    deckmock.h \
    examples_model.h \
    image_links.h \
    mainwindow.h \
    word_cards.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
