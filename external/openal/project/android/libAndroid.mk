LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libopenal.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)