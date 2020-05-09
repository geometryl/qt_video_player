QT += core gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mediaplayer
TEMPLATE = app

SOURCES += main.cpp
SOURCES += mediaplayer.cpp

HEADERS += mediaplayer.h

FORMS += mediaplayer.ui
