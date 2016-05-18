QT += core
QT -= gui

CONFIG += c++11

TARGET = gx_sl
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../../shared_src/GCSL.cpp \
    ../../../shared_src/GCSLToken.cpp \
    ../../../shared_src/GCSLError.cpp \
    ../../../shared_src/GCTextEditor.cpp

HEADERS += \
    ../../../shared_src/GCSL.h \
    ../../../shared_src/GCSLToken.h \
    ../../../shared_src/GCSLError.h \
    ../../../shared_src/GCTextEditor.h
