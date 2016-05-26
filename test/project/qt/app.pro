#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T22:22:55
#
#-------------------------------------------------

!include( config.pri ) {
    error(" Couldn't find the config.pri file! ")
}
!include( $$GX_ROOT/product/qt/GX.pri ) {
    error(" Couldn't find the GX.pri file! ")
}



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
