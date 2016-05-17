QT += core
QT -= gui

CONFIG += c++11

TARGET = gx_sl
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../../shared_src/GCSL.cpp

HEADERS += \
    ../../../shared_src/GCSL.h
