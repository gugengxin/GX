
QT       += opengl

DEFINES += GX_OS_QT

INCLUDEPATH += $$GX_ROOT/src
DEPENDPATH += $$GX_ROOT/src

LIBS += -L$$GX_ROOT/product/qt -lGX
win32 {
    INCLUDEPATH += $$GX_ROOT/external/pthread-win32/include
    DEPENDPATH += $$GX_ROOT/external/pthread-win32/include
    debug {
        LIBS += -L$$GX_ROOT/external/pthread-win32/lib/win/vc120/x64/debug/ -lpthread_dll
    }
    release {
        LIBS += -L$$GX_ROOT/external/pthread-win32/lib/win/vc120/x64/release/ -lpthread_dll
    }
}
