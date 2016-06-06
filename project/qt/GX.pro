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
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc
MOC_DIR = moc

SOURCES += \
    ../../src/GAction.cpp \
    ../../src/GApplication.cpp \
    ../../src/GArray.cpp \
    ../../src/GAutoreleasePool.cpp \
    #../../src/GBuffer.cpp \
    ../../src/GClass.cpp \
    ../../src/GColor.cpp \
    ../../src/GCondition.cpp \
    ../../src/GContext.cpp \
    #../../src/GD3DContext.cpp \
    ../../src/GData.cpp \
    ../../src/GDataArray.cpp \
    ../../src/GDataBuffer.cpp \
    ../../src/GDataString.cpp \
    #../../src/GDShader.cpp \
    #../../src/GJavaAPI.cpp \
    #../../src/GJavaCAPI.cpp \
    #../../src/GJavaClass.cpp \
    #../../src/GJavaJAPI.cpp \
    #../../src/glew.c \
    ../../src/GLog.cpp \
    ../../src/GMap.cpp \
    ../../src/GMatrix.cpp \
    ../../src/GMutex.cpp \
    ../../src/GNotice.cpp \
    ../../src/GNoticeCenter.cpp \
    ../../src/GNumber.cpp \
    ../../src/GObject.cpp \
    ../../src/GOGLContext.cpp \
    ../../src/GOShader.cpp \
    ../../src/GOWHash.cpp \
    ../../src/GPainter.cpp \
    ../../src/GPieceData.cpp \
    ../../src/GPtr.cpp \
    ../../src/GRunLoop.cpp \
    ../../src/GShader.cpp \
    ../../src/GSRGraphics.cpp \
    ../../src/GString.cpp \
    ../../src/GSystem.cpp \
    ../../src/GThread.cpp \
    ../../src/GTString.cpp \
    ../../src/GUUID.cpp \
    ../../src/GVector.cpp \
    ../../src/GWindow.cpp \
    ../../src/GWString.cpp \
    #../../src/GXCWnd.cpp \
    #../../src/GXDirectX.cpp \
    ../../src/GXMath.cpp \
    ../../src/GXOpenGL.cpp \
    #../../src/GXPthread.cpp \


win32 {
    SOURCES += ../../src/GXPthread.cpp
}

HEADERS += \
    ../../src/com_gxengine_gx_GJavaJAPI.h \
    ../../src/com_gxengine_GX.h \
    ../../src/GAction.h \
    ../../src/GApplication.h \
    ../../src/GArray.h \
    ../../src/GAutoreleasePool.h \
    ../../src/GBuffer.h \
    ../../src/GClass.h \
    ../../src/GColor.h \
    ../../src/GCondition.h \
    ../../src/GContext.h \
    ../../src/GD3DContext.h \
    ../../src/GData.h \
    ../../src/GDataArray.h \
    ../../src/GDataBuffer.h \
    ../../src/GDataString.h \
    ../../src/GDShader.h \
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
    ../../src/GObject.h \
    ../../src/GOGLContext.h \
    ../../src/GOShader.h \
    ../../src/GOWHash.h \
    ../../src/GPainter.h \
    ../../src/GPieceData.h \
    ../../src/GPtr.h \
    ../../src/GRunLoop.h \
    ../../src/GShader.h \
    ../../src/GSRGraphics.h \
    ../../src/GString.h \
    ../../src/GSystem.h \
    ../../src/GThread.h \
    ../../src/GTString.h \
    ../../src/GUUID.h \
    ../../src/GVector.h \
    ../../src/GWindow.h \
    ../../src/GWString.h \
    ../../src/GX.h \
    ../../src/GXCWnd.h \
    ../../src/GXDirectX.h \
    ../../src/GXEncoding.h \
    ../../src/GXMath.h \
    ../../src/GXOpenGL.h \
    ../../src/GXOSs.h \
    ../../src/GXPrefix.h \
    ../../src/GXPthread.h \
    ../../src/GXTypes.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
win32-msvc2013 {
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


