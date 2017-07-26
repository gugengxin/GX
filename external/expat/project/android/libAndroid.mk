LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := gx_expat
LOCAL_MODULE_FILENAME := expat
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libexpat.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include $(LOCAL_PATH)/../../include/ard/$(TARGET_ARCH_ABI)
include $(PREBUILT_STATIC_LIBRARY)