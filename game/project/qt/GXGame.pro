#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T12:27:12
#
#-------------------------------------------------

QT       += widgets opengl

TARGET = GXGame
TEMPLATE = lib
CONFIG += staticlib
macx {
    QMAKE_MAC_SDK = macosx10.12
    #QMAKE_CXXFLAGS_WARN_ON += -Wno-overloaded-virtual
    #QMAKE_CXXFLAGS += -Wno-overloaded-virtual
}
DEFINES += GX_OS_QT
win32:DEFINES += _UNICODE
DESTDIR = ../../product/qt
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc
MOC_DIR = moc

SOURCES += \
#__SOURCES_START__
	#../../src/GAndroidActivity.cpp\
	#../../src/GAndroidDaydream.cpp\
	#../../src/GAndroidEntrance.cpp\
	../../src/GBaseContext.cpp\
	../../src/GBuffer.cpp\
	../../src/GCanvas.cpp\
	../../src/GContext.cpp\
	#../../src/GD3DContext.cpp\
	#../../src/GDShader.cpp\
	../../src/GFrameBuffer.cpp\
	../../src/GGame.cpp\
	../../src/GGameResManager.cpp\
	../../src/GIndexBuffer.cpp\
	#../../src/GMShader.cpp\
	#../../src/GMTLContext.cpp\
	../../src/GOGLContext.cpp\
	../../src/GOShader.cpp\
	../../src/GSRGraphics.cpp\
	../../src/GSRTexture2D.cpp\
	../../src/GShader.cpp\
	../../src/GTex2DFont.cpp\
	../../src/GTexture.cpp\
	../../src/GTexture1D.cpp\
	../../src/GTexture2D.cpp\
	../../src/GTextureCube.cpp\
	../../src/GWindow.cpp\
	../../src/GX3DAPI.cpp\
	#../../src/GXDirectX.cpp\
	#../../src/GXMetal.cpp\
	../../src/GXOpenGL.cpp\
	#../../src/glew.c\
#__SOURCES_END__

HEADERS += \
#__HEADERS_START__
	../../src/GAndroidActivity.h\
	../../src/GAndroidDaydream.h\
	../../src/GAndroidEntrance.h\
	../../src/GBaseContext.h\
	../../src/GBuffer.h\
	../../src/GCanvas.h\
	../../src/GContext.h\
	../../src/GD3DContext.h\
	../../src/GDShader.h\
	../../src/GFrameBuffer.h\
	../../src/GGame.h\
	../../src/GGameResManager.h\
	../../src/GIndexBuffer.h\
	../../src/GL/eglew.h\
	../../src/GL/glew.h\
	../../src/GL/glxew.h\
	../../src/GL/wglew.h\
	../../src/GMShader.h\
	../../src/GMTLContext.h\
	../../src/GOGLContext.h\
	../../src/GOShader.h\
	../../src/GSRGraphics.h\
	../../src/GSRTexture2D.h\
	../../src/GShader.h\
	../../src/GTex2DFont.h\
	../../src/GTexture.h\
	../../src/GTexture1D.h\
	../../src/GTexture2D.h\
	../../src/GTextureCube.h\
	../../src/GWindow.h\
	../../src/GX3DAPI.h\
	../../src/GX3DAPIPre.h\
	../../src/GX3DAPIType.h\
	../../src/GXContext.h\
	../../src/GXDirectX.h\
	../../src/GXGame.h\
	../../src/GXMetal.h\
	../../src/GXOpenGL.h\
	../../src/com_gxengine_game_GAndroidActivity.h\
	../../src/com_gxengine_game_GAndroidDaydream.h\
#__HEADERS_END__


unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../../../core/src


