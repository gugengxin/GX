QT += core
QT -= gui

CONFIG += c++11

TARGET = gx_sed
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../../shared_src/GCSed.cpp

HEADERS += \
    ../../../shared_src/GCSed.h
