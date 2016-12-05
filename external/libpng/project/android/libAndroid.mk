LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := gx_libpng
LOCAL_MODULE_FILENAME := libpng
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../../include $(LOCAL_PATH)/../../../../zlib/include
LOCAL_STATIC_LIBRARIES := gx_zlib
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libpng.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)