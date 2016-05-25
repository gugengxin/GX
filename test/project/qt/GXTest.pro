#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T22:22:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GXTest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ../../src/AppDge.cpp

HEADERS  += MainWindow.h \
    ../../src/AppDge.h

FORMS    += MainWindow.ui

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src
