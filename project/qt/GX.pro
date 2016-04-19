#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T12:27:12
#
#-------------------------------------------------

QT       += widgets opengl

TARGET = GX
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    ../../src/GClass.cpp \
    ../../src/GObject.cpp \
    ../../src/GOWHash.cpp

HEADERS += \
    ../../src/GClass.h \
    ../../src/GObject.h \
    ../../src/GOWHash.h \
    ../../src/GX.h \
    ../../src/GXOSs.h \
    ../../src/GXPrefix.h \
    ../../src/GXTypes.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
