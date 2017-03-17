
macx {
    QMAKE_MAC_SDK = macosx10.12
    #QMAKE_CXXFLAGS_WARN_ON += -Wno-overloaded-virtual
    #QMAKE_CXXFLAGS += -Wno-overloaded-virtual
}
DEFINES += GX_OS_QT
win32:DEFINES += _UNICODE

INCLUDEPATH += $$GX_ROOT/core/src
DEPENDPATH += $$GX_ROOT/core/src

LIBS += -L$$GX_ROOT/core/product/qt -lGXCore
#libs
win32 {
    debug {
        LIBS += -L$$GX_ROOT/external/pthread-win32/lib/win/vc120/x64/debug/ -lpthread_dll
        LIBS += -L$$GX_ROOT/external/zlib/lib/win/vc120/x64/debug/ -lzlib
        LIBS += -L$$GX_ROOT/external/libpng/lib/win/vc120/x64/debug/ -llibpng
        LIBS += -L$$GX_ROOT/external/libjpeg/lib/win/vc120/x64/debug/ -llibjpeg
    }
    release {
        LIBS += -L$$GX_ROOT/external/pthread-win32/lib/win/vc120/x64/release/ -lpthread_dll
        LIBS += -L$$GX_ROOT/external/zlib/lib/win/vc120/x64/release/ -lzlib
        LIBS += -L$$GX_ROOT/external/libpng/lib/win/vc120/x64/release/ -llibpng
        LIBS += -L$$GX_ROOT/external/libjpeg/lib/win/vc120/x64/release/ -llibjpeg
    }
}
else:macx {
    LIBS += -framework CoreFoundation
    LIBS += -L$$GX_ROOT/external/zlib/lib/mac/ -lzlib
    LIBS += -L$$GX_ROOT/external/libpng/lib/mac/ -llibpng
    LIBS += -L$$GX_ROOT/external/libjpeg/lib/mac/ -llibjpeg
}
#dlls
win32{
    WIN_GX_ROOT = $$GX_ROOT
    WIN_GX_ROOT ~= s,/,\\,g
    debug {
        QMAKE_POST_LINK = copy /y $$WIN_GX_ROOT\\external\\pthread-win32\\lib\\win\\vc120\\x64\\debug\\*.dll Debug
    }
    else {
        QMAKE_POST_LINK = copy /y $$WIN_GX_ROOT\\external\\pthread-win32\\lib\\win\\vc120\\x64\\release\\*.dll Release
    }
}
