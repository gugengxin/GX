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
    ../../../shared_src/GCTextEditor.cpp \
    ../../../shared_src/GCSLWriter.cpp \
    ../../../shared_src/GCSLWRoot.cpp \
    ../../../shared_src/GCSLReader.cpp \
    ../../../shared_src/GCSLWord.cpp \
    ../../../shared_src/GCSLTokenReader.cpp \
    ../../../shared_src/GCSLWHT.cpp

HEADERS += \
    ../../../shared_src/GCSL.h \
    ../../../shared_src/GCSLToken.h \
    ../../../shared_src/GCSLError.h \
    ../../../shared_src/GCTextEditor.h \
    ../../../shared_src/GCSLWriter.h \
    ../../../shared_src/GCSLWRoot.h \
    ../../../shared_src/GCSLReader.h \
    ../../../shared_src/GCSLWord.h \
    ../../../shared_src/GCSLTokenReader.h \
    ../../../shared_src/GCSLWHT.h
