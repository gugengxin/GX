#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T10:10:21
#
#-------------------------------------------------

QT       -= gui

TARGET = GXCore
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
    #QMAKE_MAC_SDK = macosx10.12
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
	../../src/GAction.cpp\
	#../../src/GAndroidApp.cpp\
	../../src/GAppBundle.cpp\
	../../src/GApplication.cpp\
	../../src/GArray.cpp\
	../../src/GAutoreleasePool.cpp\
	../../src/GBundle.cpp\
	../../src/GClass.cpp\
	../../src/GCoder.cpp\
	../../src/GColor.cpp\
	../../src/GCondition.cpp\
	../../src/GData.cpp\
	../../src/GDataArray.cpp\
	../../src/GDataList.cpp\
	../../src/GDataReader.cpp\
	../../src/GDataWriter.cpp\
	../../src/GDib.cpp\
	../../src/GError.cpp\
	../../src/GFileBundle.cpp\
	../../src/GFileManager.cpp\
	../../src/GFileReader.cpp\
	../../src/GFileWriter.cpp\
	#../../src/GJNI.cpp\
	../../src/GJpeg.cpp\
	../../src/GList.cpp\
	../../src/GLog.cpp\
	../../src/GMap.cpp\
	../../src/GMatrix.cpp\
	../../src/GMutex.cpp\
	../../src/GNotice.cpp\
	../../src/GNoticeCenter.cpp\
	../../src/GNumber.cpp\
	../../src/GOWHash.cpp\
	../../src/GObject.cpp\
	../../src/GPieceData.cpp\
	../../src/GPng.cpp\
	../../src/GPtr.cpp\
	../../src/GRBReader.cpp\
	../../src/GReader.cpp\
	../../src/GRunLoop.cpp\
	../../src/GSerialize.cpp\
	../../src/GString.cpp\
	../../src/GSystem.cpp\
	../../src/GThread.cpp\
	../../src/GUUID.cpp\
	../../src/GVector.cpp\
	../../src/GWriter.cpp\
	#../../src/GXCWnd.cpp\
	../../src/GXCoder.cpp\
	../../src/GXData.cpp\
	../../src/GXMath.cpp\
	../../src/GZipBundle.cpp\
	../../src/GZipReader.cpp\
	../../src/GZipWriter.cpp\
#__SOURCES_END__

win32 {
    SOURCES += ./../src/GXPthread.cpp
}

HEADERS += \
#__HEADERS_START__
	../../src/GAction.h\
	../../src/GAndroidApp.h\
	../../src/GAppBundle.h\
	../../src/GApplication.h\
	../../src/GArray.h\
	../../src/GAutoreleasePool.h\
	../../src/GBundle.h\
	../../src/GClass.h\
	../../src/GCoder.h\
	../../src/GColor.h\
	../../src/GCondition.h\
	../../src/GData.h\
	../../src/GDataArray.h\
	../../src/GDataList.h\
	../../src/GDataReader.h\
	../../src/GDataWriter.h\
	../../src/GDib.h\
	../../src/GError.h\
	../../src/GFileBundle.h\
	../../src/GFileManager.h\
	../../src/GFileReader.h\
	../../src/GFileWriter.h\
	../../src/GJNI.h\
	../../src/GJpeg.h\
	../../src/GList.h\
	../../src/GLog.h\
	../../src/GMap.h\
	../../src/GMatrix.h\
	../../src/GMutex.h\
	../../src/GNotice.h\
	../../src/GNoticeCenter.h\
	../../src/GNumber.h\
	../../src/GOWHash.h\
	../../src/GObject.h\
	../../src/GPieceData.h\
	../../src/GPng.h\
	../../src/GPtr.h\
	../../src/GRBReader.h\
	../../src/GReader.h\
	../../src/GRunLoop.h\
	../../src/GSerialize.h\
	../../src/GString.h\
	../../src/GSystem.h\
	../../src/GThread.h\
	../../src/GUUID.h\
	../../src/GVector.h\
	../../src/GWriter.h\
	../../src/GXCWnd.h\
	../../src/GXCoder.h\
	../../src/GXCore.h\
	../../src/GXData.h\
	../../src/GXEncoding.h\
	../../src/GXFILE.h\
	../../src/GXGObject.h\
	../../src/GXGObjectUD.h\
	../../src/GXMath.h\
	../../src/GXOS.h\
	../../src/GXObject.h\
	../../src/GXPixel.h\
	../../src/GXPrefix.h\
	../../src/GXPthread.h\
	../../src/GXTypes.h\
	../../src/GZipBundle.h\
	../../src/GZipReader.h\
	../../src/GZipWriter.h\
	../../src/com_gxengine_core_GAndroidApp.h\
#__HEADERS_END__

#pthread
win32 {
    QMAKE_LIBFLAGS += /ignore:4221
    INCLUDEPATH += $$PWD/../../../external/pthread-win32/include
}
#zlib
INCLUDEPATH += $$PWD/../../../external/zlib/include
#libpng
INCLUDEPATH += $$PWD/../../../external/libpng/include
#libjpeg
INCLUDEPATH += $$PWD/../../../external/libjpeg/include
win32:macx {
    INCLUDEPATH += $$PWD/../../../external/libjpeg/include/win
}
else:macx {
    INCLUDEPATH += $$PWD/../../../external/libjpeg/include/mac
}



