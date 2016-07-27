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
win32:DEFINES += _UNICODE
DESTDIR = ../../product/qt
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc
MOC_DIR = moc

SOURCES += \
#__SOURCES_START__
	../../src/GAction.cpp\
	../../src/GAppBundle.cpp\
	../../src/GApplication.cpp\
	../../src/GArray.cpp\
	../../src/GAutoreleasePool.cpp\
	#../../src/GBuffer.cpp\
	../../src/GBundle.cpp\
	../../src/GClass.cpp\
	../../src/GColor.cpp\
	../../src/GCondition.cpp\
	../../src/GContext.cpp\
	#../../src/GD3DContext.cpp\
	#../../src/GDShader.cpp\
	../../src/GData.cpp\
	../../src/GDataArray.cpp\
	../../src/GDataBuffer.cpp\
	../../src/GDataList.cpp\
	../../src/GDataReader.cpp\
	../../src/GDataString.cpp\
	../../src/GDataWriter.cpp\
	../../src/GFileBundle.cpp\
	../../src/GFileManager.cpp\
	../../src/GFileReader.cpp\
	../../src/GFileWriter.cpp\
	#../../src/GJavaAPI.cpp\
	#../../src/GJavaCAPI.cpp\
	#../../src/GJavaClass.cpp\
	#../../src/GJavaJAPI.cpp\
	../../src/GList.cpp\
	../../src/GLog.cpp\
	../../src/GMap.cpp\
	../../src/GMatrix.cpp\
	../../src/GMutex.cpp\
	../../src/GNotice.cpp\
	../../src/GNoticeCenter.cpp\
	../../src/GNumber.cpp\
	../../src/GOGLContext.cpp\
	../../src/GOShader.cpp\
	../../src/GOWHash.cpp\
	../../src/GObject.cpp\
	../../src/GPainter.cpp\
	../../src/GPieceData.cpp\
	../../src/GPtr.cpp\
	../../src/GRBReader.cpp\
	../../src/GReader.cpp\
	../../src/GRunLoop.cpp\
	../../src/GSRGraphics.cpp\
	../../src/GShader.cpp\
	../../src/GString.cpp\
	../../src/GSystem.cpp\
	../../src/GTString.cpp\
	../../src/GTexture.cpp\
	../../src/GTexture2D.cpp\
	../../src/GThread.cpp\
	../../src/GUUID.cpp\
	../../src/GVector.cpp\
	../../src/GWString.cpp\
	../../src/GWindow.cpp\
	../../src/GWriter.cpp\
	#../../src/GXCWnd.cpp\
	#../../src/GXDirectX.cpp\
	../../src/GXMath.cpp\
	../../src/GXOpenGL.cpp\
	../../src/GZipBundle.cpp\
	../../src/GZipReader.cpp\
	../../src/GZipWriter.cpp\
	#../../src/glew.c\
#__SOURCES_END__

win32 {
    SOURCES += ../../src/GXPthread.cpp
}

HEADERS += \
#__HEADERS_START__
	../../src/GAction.h\
	../../src/GAppBundle.h\
	../../src/GApplication.h\
	../../src/GArray.h\
	../../src/GAutoreleasePool.h\
	../../src/GBuffer.h\
	../../src/GBundle.h\
	../../src/GClass.h\
	../../src/GColor.h\
	../../src/GCondition.h\
	../../src/GContext.h\
	../../src/GD3DContext.h\
	../../src/GDShader.h\
	../../src/GData.h\
	../../src/GDataArray.h\
	../../src/GDataBuffer.h\
	../../src/GDataList.h\
	../../src/GDataReader.h\
	../../src/GDataString.h\
	../../src/GDataWriter.h\
	../../src/GFileBundle.h\
	../../src/GFileManager.h\
	../../src/GFileReader.h\
	../../src/GFileWriter.h\
	../../src/GJavaAPI.h\
	../../src/GJavaCAPI.h\
	../../src/GJavaClass.h\
	../../src/GJavaJAPI.h\
	../../src/GL/glew.h\
	../../src/GL/glxew.h\
	../../src/GL/wglew.h\
	../../src/GList.h\
	../../src/GLog.h\
	../../src/GMap.h\
	../../src/GMatrix.h\
	../../src/GMutex.h\
	../../src/GNotice.h\
	../../src/GNoticeCenter.h\
	../../src/GNumber.h\
	../../src/GOGLContext.h\
	../../src/GOShader.h\
	../../src/GOWHash.h\
	../../src/GObject.h\
	../../src/GPainter.h\
	../../src/GPieceData.h\
	../../src/GPtr.h\
	../../src/GRBReader.h\
	../../src/GReader.h\
	../../src/GRunLoop.h\
	../../src/GSRGraphics.h\
	../../src/GShader.h\
	../../src/GString.h\
	../../src/GSystem.h\
	../../src/GTString.h\
	../../src/GTexture.h\
	../../src/GTexture2D.h\
	../../src/GThread.h\
	../../src/GUUID.h\
	../../src/GVector.h\
	../../src/GWString.h\
	../../src/GWindow.h\
	../../src/GWriter.h\
	../../src/GX.h\
	../../src/GXCWnd.h\
	../../src/GXDirectX.h\
	../../src/GXEncoding.h\
	../../src/GXFILE.h\
	../../src/GXGObject.h\
	../../src/GXGObjectUD.h\
	../../src/GXMath.h\
	../../src/GXOSs.h\
	../../src/GXObject.h\
	../../src/GXOpenGL.h\
	../../src/GXPrefix.h\
	../../src/GXPthread.h\
	../../src/GXTypes.h\
	../../src/GZipBundle.h\
	../../src/GZipReader.h\
	../../src/GZipWriter.h\
	../../src/com_gxengine_GX.h\
	../../src/com_gxengine_gx_GJavaJAPI.h\
#__HEADERS_END__


unix {
    target.path = /usr/lib
    INSTALLS += target
}
#pthread
win32-msvc2013 {
    QMAKE_LIBFLAGS += /ignore:4221
    INCLUDEPATH += $$PWD/../../external/pthread-win32/include
}
#zlib
INCLUDEPATH += $$PWD/../../external/zlib/include


