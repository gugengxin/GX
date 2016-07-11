LOCAL_PATH := $(call my-dir)

ENGINE_PATH := $(LOCAL_PATH)/../../../../../../..
ENGINE_PATH_FROM_SRC := ../../../../../../..

#Android与系统交互部分
include $(CLEAR_VARS)
LOCAL_MODULE    := GXAndroid
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/src
LOCAL_CFLAGS 	+= -Wno-multichar -D GX_OS_ANDROID
LOCAL_CPPFLAGS	+= -fno-rtti #-fvisibility=hidden -std=c++11
LOCAL_SRC_FILES := \
 $(ENGINE_PATH_FROM_SRC)/src/GJavaAPI.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GJavaCAPI.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GJavaClass.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GJavaJAPI.cpp \

include $(BUILD_STATIC_LIBRARY)


