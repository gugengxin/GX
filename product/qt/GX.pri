
QT       += opengl

DEFINES += GX_OS_QT

INCLUDEPATH += $$GX_ROOT/src
DEPENDPATH += $$GX_ROOT/src

LIBS += -L$$GX_ROOT/product/qt -lGX

#pthread
win32 {
    debug {
        LIBS += -L$$GX_ROOT/external/pthread-win32/lib/win/vc120/x64/debug/ -lpthread_dll
    }
    release {
        LIBS += -L$$GX_ROOT/external/pthread-win32/lib/win/vc120/x64/release/ -lpthread_dll
    }
}

#zlib
macx {
    LIBS += -L$$GX_ROOT/external/zlib/lib/mac/ -lzlib
}

