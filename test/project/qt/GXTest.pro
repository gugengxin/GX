!include( config.pri ) {
    error(" Couldn't find the config.pri file! ")
}

TEMPLATE = subdirs
SUBDIRS = GX GXTest
GX.file = $$GX_ROOT/project/qt/GX.pro
GXTest.file = ./app.pro
GXTest.depends = GX
CONFIG += ordered

