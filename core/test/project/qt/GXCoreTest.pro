!include( config.pri ) {
    error(" Couldn't find the config.pri file! ")
}

TEMPLATE = subdirs

SUBDIRS = GXCore GXCoreTest

GXCore.file = ../../../project/qt/GXCore.pro

GXCoreTest.file = app.pro
GXCoreTest.depends = GXCore

CONFIG += ordered
