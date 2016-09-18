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

APP_RES_FILES.files = $$PWD/../../assets/lena_rgb.jpg
APP_RES_FILES.path = Contents/Resources

QMAKE_BUNDLE_DATA += APP_RES_FILES

#assets
win32{
    WIN_ASSETS_SRC = $$PWD/../../assets
    WIN_ASSETS_SRC ~= s,/,\\,g
    QMAKE_POST_LINK = xcopy /i /e /y $$WIN_ASSETS_SRC assets
}
