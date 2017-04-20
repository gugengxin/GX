!include( config.pri ) {
    error(" Couldn't find the config.pri file! ")
}

TEMPLATE = subdirs
SUBDIRS = GXCore GXGame GXGameTest
GXCore.file = $$GX_ROOT/core/project/qt/GXCore.pro
GXGame.file = $$GX_ROOT/game/project/qt/GXGame.pro
GXGameTest.file = ./app.pro
GXGameTest.depends = GXCore GXGame
CONFIG += ordered

