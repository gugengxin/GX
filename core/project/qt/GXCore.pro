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
\t../../src/GAction.cpp\\\n\t#../../src/GAndroidApp.cpp\\\n\t../../src/GAppBundle.cpp\\\n\t../../src/GApplication.cpp\\\n\t../../src/GArray.cpp\\\n\t../../src/GAutoreleasePool.cpp\\\n\t../../src/GBundle.cpp\\\n\t../../src/GClass.cpp\\\n\t../../src/GCoder.cpp\\\n\t../../src/GColor.cpp\\\n\t../../src/GCondition.cpp\\\n\t../../src/GData.cpp\\\n\t../../src/GDataArray.cpp\\\n\t../../src/GDataList.cpp\\\n\t../../src/GDataReader.cpp\\\n\t../../src/GDataWriter.cpp\\\n\t../../src/GDib.cpp\\\n\t../../src/GError.cpp\\\n\t../../src/GFileBundle.cpp\\\n\t../../src/GFileManager.cpp\\\n\t../../src/GFileReader.cpp\\\n\t../../src/GFileWriter.cpp\\\n\t#../../src/GJNI.cpp\\\n\t../../src/GJpeg.cpp\\\n\t../../src/GList.cpp\\\n\t../../src/GLog.cpp\\\n\t../../src/GMap.cpp\\\n\t../../src/GMatrix.cpp\\\n\t../../src/GMutex.cpp\\\n\t../../src/GNotice.cpp\\\n\t../../src/GNoticeCenter.cpp\\\n\t../../src/GNumber.cpp\\\n\t../../src/GOWHash.cpp\\\n\t../../src/GObject.cpp\\\n\t../../src/GPieceData.cpp\\\n\t../../src/GPng.cpp\\\n\t../../src/GPtr.cpp\\\n\t../../src/GRBReader.cpp\\\n\t../../src/GReader.cpp\\\n\t../../src/GRunLoop.cpp\\\n\t../../src/GSerialize.cpp\\\n\t../../src/GString.cpp\\\n\t../../src/GSystem.cpp\\\n\t../../src/GThread.cpp\\\n\t../../src/GUUID.cpp\\\n\t../../src/GVector.cpp\\\n\t../../src/GWriter.cpp\\\n\t#../../src/GXCWnd.cpp\\\n\t../../src/GXCoder.cpp\\\n\t../../src/GXData.cpp\\\n\t../../src/GXMath.cpp\\\n\t../../src/GZipBundle.cpp\\\n\t../../src/GZipReader.cpp\\\n\t../../src/GZipWriter.cpp\\\n#__SOURCES_END__

win32 {
    SOURCES += ./../src/GXPthread.cpp
}

HEADERS += \
#__HEADERS_START__
\t../../src/GAction.h\\\n\t../../src/GAndroidApp.h\\\n\t../../src/GAppBundle.h\\\n\t../../src/GApplication.h\\\n\t../../src/GArray.h\\\n\t../../src/GAutoreleasePool.h\\\n\t../../src/GBundle.h\\\n\t../../src/GClass.h\\\n\t../../src/GCoder.h\\\n\t../../src/GColor.h\\\n\t../../src/GCondition.h\\\n\t../../src/GData.h\\\n\t../../src/GDataArray.h\\\n\t../../src/GDataList.h\\\n\t../../src/GDataReader.h\\\n\t../../src/GDataWriter.h\\\n\t../../src/GDib.h\\\n\t../../src/GError.h\\\n\t../../src/GFileBundle.h\\\n\t../../src/GFileManager.h\\\n\t../../src/GFileReader.h\\\n\t../../src/GFileWriter.h\\\n\t../../src/GJNI.h\\\n\t../../src/GJpeg.h\\\n\t../../src/GList.h\\\n\t../../src/GLog.h\\\n\t../../src/GMap.h\\\n\t../../src/GMatrix.h\\\n\t../../src/GMutex.h\\\n\t../../src/GNotice.h\\\n\t../../src/GNoticeCenter.h\\\n\t../../src/GNumber.h\\\n\t../../src/GOWHash.h\\\n\t../../src/GObject.h\\\n\t../../src/GPieceData.h\\\n\t../../src/GPng.h\\\n\t../../src/GPtr.h\\\n\t../../src/GRBReader.h\\\n\t../../src/GReader.h\\\n\t../../src/GRunLoop.h\\\n\t../../src/GSerialize.h\\\n\t../../src/GString.h\\\n\t../../src/GSystem.h\\\n\t../../src/GThread.h\\\n\t../../src/GUUID.h\\\n\t../../src/GVector.h\\\n\t../../src/GWriter.h\\\n\t../../src/GXCWnd.h\\\n\t../../src/GXCoder.h\\\n\t../../src/GXCore.h\\\n\t../../src/GXData.h\\\n\t../../src/GXEncoding.h\\\n\t../../src/GXFILE.h\\\n\t../../src/GXGObject.h\\\n\t../../src/GXGObjectUD.h\\\n\t../../src/GXMath.h\\\n\t../../src/GXOS.h\\\n\t../../src/GXObject.h\\\n\t../../src/GXPixel.h\\\n\t../../src/GXPrefix.h\\\n\t../../src/GXPthread.h\\\n\t../../src/GXTypes.h\\\n\t../../src/GZipBundle.h\\\n\t../../src/GZipReader.h\\\n\t../../src/GZipWriter.h\\\n\t../../src/com_gxengine_core_GAndroidApp.h\\\n#__HEADERS_END__

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
    INCLUDEPATH += $$PWD/../../../external/libjpeg/include/mac
}
else:macx {
    INCLUDEPATH += $$PWD/../../../external/libjpeg/include/mac
}



