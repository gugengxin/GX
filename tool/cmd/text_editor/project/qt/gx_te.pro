QT += core
QT -= gui

CONFIG += c++11

TARGET = gx_te
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../../shared_src/GCTextEditor.cpp

HEADERS += \
    ../../../shared_src/GCTextEditor.h

INCLUDEPATH += $$PWD/../../../shared_src
