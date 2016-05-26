#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T12:27:12
#
#-------------------------------------------------

QT       += widgets opengl

TARGET = GX
TEMPLATE = lib
CONFIG += staticlib
DEFINES += GX_OS_QT
DESTDIR = ../../product/qt

SOURCES += \
    ../../src/GClass.cpp \
    ../../src/GObject.cpp \
    ../../src/GOWHash.cpp \
    ../../src/GAction.cpp \
    ../../src/GApplication.cpp \
    ../../src/GArray.cpp \
    ../../src/GAutoreleasePool.cpp \
    ../../src/GCondition.cpp \
    ../../src/GContext.cpp \
    ../../src/GD3DContext.cpp \
    ../../src/GData.cpp \
    ../../src/GDataArray.cpp \
    ../../src/GDataString.cpp \
    ../../src/GJavaAPI.cpp \
    ../../src/GJavaCAPI.cpp \
    ../../src/GJavaClass.cpp \
    ../../src/GJavaJAPI.cpp \
    ../../src/GLog.cpp \
    ../../src/GMap.cpp \
    ../../src/GMatrix.cpp \
    ../../src/GMutex.cpp \
    ../../src/GNotice.cpp \
    ../../src/GNoticeCenter.cpp \
    ../../src/GNumber.cpp \
    ../../src/GOGLContext.cpp \
    ../../src/GPieceData.cpp \
    ../../src/GPtr.cpp \
    ../../src/GRunLoop.cpp \
    ../../src/GShader.cpp \
    ../../src/GString.cpp \
    ../../src/GSystem.cpp \
    ../../src/GThread.cpp \
    ../../src/GTString.cpp \
    ../../src/GUUID.cpp \
    ../../src/GVector.cpp \
    ../../src/GWindow.cpp \
    ../../src/GWString.cpp \
    ../../src/GXCWnd.cpp \
    ../../src/GXDirectX.cpp \
    ../../src/GXMath.cpp \
    ../../src/GXOpenGL.cpp \
    ../../src/GXPthread.cpp \
    ../../src/glew.c

HEADERS += \
    ../../src/GClass.h \
    ../../src/GObject.h \
    ../../src/GOWHash.h \
    ../../src/GX.h \
    ../../src/GXOSs.h \
    ../../src/GXPrefix.h \
    ../../src/GXTypes.h \
    ../../src/com_gxengine_GX.h \
    ../../src/com_gxengine_gx_GJavaJAPI.h \
    ../../src/GAction.h \
    ../../src/GApplication.h \
    ../../src/GArray.h \
    ../../src/GAutoreleasePool.h \
    ../../src/GCondition.h \
    ../../src/GContext.h \
    ../../src/GD3DContext.h \
    ../../src/GData.h \
    ../../src/GDataArray.h \
    ../../src/GDataString.h \
    ../../src/GJavaAPI.h \
    ../../src/GJavaCAPI.h \
    ../../src/GJavaClass.h \
    ../../src/GJavaJAPI.h \
    ../../src/GLog.h \
    ../../src/GMap.h \
    ../../src/GMatrix.h \
    ../../src/GMutex.h \
    ../../src/GNotice.h \
    ../../src/GNoticeCenter.h \
    ../../src/GNumber.h \
    ../../src/GOGLContext.h \
    ../../src/GPieceData.h \
    ../../src/GPtr.h \
    ../../src/GRunLoop.h \
    ../../src/GShader.h \
    ../../src/GString.h \
    ../../src/GSystem.h \
    ../../src/GThread.h \
    ../../src/GTString.h \
    ../../src/GUUID.h \
    ../../src/GVector.h \
    ../../src/GWindow.h \
    ../../src/GWString.h \
    ../../src/GXCWnd.h \
    ../../src/GXDirectX.h \
    ../../src/GXEncoding.h \
    ../../src/GXMath.h \
    ../../src/GXOpenGL.h \
    ../../src/GXPthread.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
win32 {
    QMAKE_LIBFLAGS += /ignore:4221
    INCLUDEPATH += $$PWD/../../external/pthread-win32/include
    DEPENDPATH += $$PWD/../../external/pthread-win32/include
    debug {
        LIBS += -L$$PWD/../../external/pthread-win32/lib/win/vc120/x64/debug/ -lpthread_dll
    }
    release {
        LIBS += -L$$PWD/../../external/pthread-win32/lib/win/vc120/x64/release/ -lpthread_dll
    }
}


