LOCAL_PATH := $(call my-dir)

ENGINE_PATH := $(LOCAL_PATH)/../../../../../../..
ENGINE_PATH_FROM_SRC := ../../../../../../..

$(call import-add-path,$(ENGINE_PATH))

#Android与系统交互部分
include $(CLEAR_VARS)
LOCAL_MODULE    := GXCoreAndroid
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/src
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
LOCAL_EXPORT_LDLIBS := -llog -landroid
#__LOCAL_SRC_FILES_START__
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GAction.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GAppBundle.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GApplication.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GArray.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GAutoreleasePool.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GBundle.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GClass.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GCoder.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GColor.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GCondition.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GData.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataArray.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataList.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataReader.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDataWriter.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GDib.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GError.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileBundle.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileManager.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileReader.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GFileWriter.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GJpeg.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GList.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GLog.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GMap.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GMatrix.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GMutex.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GNotice.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GNoticeCenter.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GNumber.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GOWHash.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GObject.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GPieceData.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GPng.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GPtr.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GRBReader.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GReader.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GRunLoop.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GSerialize.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GString.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GSystem.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GThread.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GUUID.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GVector.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GWriter.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXCWnd.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXCoder.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXData.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXMath.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GXPthread.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GZipBundle.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GZipReader.cpp\nLOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src/GZipWriter.cpp\n#__LOCAL_SRC_FILES_END__

include $(BUILD_STATIC_LIBRARY)

$(call import-module,external/zlib/lib/ard)
$(call import-module,external/libpng/lib/ard)
$(call import-module,external/libjpeg/lib/ard)


