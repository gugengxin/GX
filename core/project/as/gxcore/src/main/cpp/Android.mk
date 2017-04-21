LOCAL_PATH := $(call my-dir)

ENGINE_PATH := $(LOCAL_PATH)/../../../../../../..
ENGINE_PATH_FROM_SRC := ../../../../../../..

$(call import-add-path,$(ENGINE_PATH))

#Android与系统交互部分
include $(CLEAR_VARS)
LOCAL_MODULE    := GXCoreAndroid
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/core/src
LOCAL_CFLAGS 	+= -Wno-multichar
LOCAL_CPPFLAGS	+= -fno-rtti
LOCAL_SRC_FILES := \
 $(ENGINE_PATH_FROM_SRC)/core/src/GJNI.cpp \
 $(ENGINE_PATH_FROM_SRC)/core/src/GAndroidApp.cpp \

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := GXCore
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/core/src
LOCAL_EXPORT_C_INCLUDES:= $(ENGINE_PATH)/core/src
LOCAL_CFLAGS 	+= -Wno-multichar
LOCAL_CPPFLAGS	+= -fno-rtti
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS)
LOCAL_WHOLE_STATIC_LIBRARIES := GXCoreAndroid
LOCAL_STATIC_LIBRARIES	:= gx_zlib gx_libpng gx_libjpeg
#LOCAL_LDLIBS 	:=
LOCAL_EXPORT_LDLIBS := -landroid -llog
#__LOCAL_SRC_FILES_START__
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GAction.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GAppBundle.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GApplication.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GArray.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GAutoreleasePool.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GBundle.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GClass.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GCoder.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GColor.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GCondition.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GData.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataArray.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataList.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataReader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataWriter.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDib.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GError.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileBundle.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileManager.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileReader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileWriter.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GJpeg.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GList.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GLog.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GMap.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GMatrix.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GMutex.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GNotice.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GNoticeCenter.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GNumber.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GOWHash.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GObject.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GPieceData.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GPng.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GPtr.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GRBReader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GReader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GRunLoop.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GSerialize.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GString.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GSystem.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GThread.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GUUID.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GVector.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GWriter.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXCWnd.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXCoder.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXData.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXMath.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXPthread.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GZipBundle.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GZipReader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GZipWriter.cpp
#__LOCAL_SRC_FILES_END__

include $(BUILD_STATIC_LIBRARY)

$(call import-module,external/zlib/lib/ard)
$(call import-module,external/libpng/lib/ard)
$(call import-module,external/libjpeg/lib/ard)


