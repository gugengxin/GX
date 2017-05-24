LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := gx_harfbuzz
LOCAL_MODULE_FILENAME := harfbuzz
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/harfbuzz.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_STATIC_LIBRARY)