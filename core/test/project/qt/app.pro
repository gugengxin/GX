#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T13:02:23
#
#-------------------------------------------------
!include( config.pri ) {
    error(" Couldn't find the config.pri file! ")
}
!include( $$GX_ROOT/core/product/qt/GXCore.pri ) {
    error(" Couldn't find the GXCore.pri file! ")
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GXCoreTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../src
DEPENDPATH += ../../src
SOURCES += \
        ../../src/AppDge.cpp

HEADERS  += \
        ../../src/AppDge.h

SOURCES += \
        main.cpp\
        mainwindow.cpp

HEADERS  += \
        mainwindow.h

FORMS    += mainwindow.ui
