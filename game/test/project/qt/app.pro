#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T22:22:55
#
#-------------------------------------------------

!include( config.pri ) {
    error(" Couldn't find the config.pri file! ")
}
!include( $$GX_ROOT/core/product/qt/GXCore.pri ) {
    error(" Couldn't find the GXCore.pri file! ")
}
!include( $$GX_ROOT/game/product/qt/GXGame.pri ) {
    error(" Couldn't find the GXGame.pri file! ")
}



QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GXGameTest
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ../../src/AppDge.cpp \
    ../../src/Game.cpp \
    ../../src/Module.cpp \
    ../../src/MGraphics.cpp \
    ../../src/MFrameBuffer.cpp \
    ../../src/MTypist.cpp \

HEADERS  += MainWindow.h \
    ../../src/AppDge.h \
    ../../src/Game.h \
    ../../src/Module.h \
    ../../src/MGraphics.h \
    ../../src/MFrameBuffer.h \
    ../../src/MTypist.h \

FORMS    += MainWindow.ui

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src

APP_RES_FILES.files = $$files($$PWD/../../assets/*.*)
APP_RES_FILES.path = Contents/Resources

QMAKE_BUNDLE_DATA += APP_RES_FILES

#assets
win32{
    WIN_ASSETS_SRC = $$PWD/../../assets
    WIN_ASSETS_SRC ~= s,/,\\,g
    QMAKE_POST_LINK = xcopy /i /e /y $$WIN_ASSETS_SRC assets
}
