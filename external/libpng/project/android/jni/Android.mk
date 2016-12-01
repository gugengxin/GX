LOCAL_PATH := $(call my-dir)

PATH_FROM_SRC := ../../../src

include $(CLEAR_VARS)

LOCAL_MODULE    := png
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../../include $(LOCAL_PATH)/../../../../zlib/include
LOCAL_SRC_FILES := \
$(PATH_FROM_SRC)/png.c\
$(PATH_FROM_SRC)/pngerror.c\
$(PATH_FROM_SRC)/pngget.c\
$(PATH_FROM_SRC)/pngmem.c\
$(PATH_FROM_SRC)/pngpread.c\
$(PATH_FROM_SRC)/pngread.c\
$(PATH_FROM_SRC)/pngrio.c\
$(PATH_FROM_SRC)/pngrtran.c\
$(PATH_FROM_SRC)/pngrutil.c\
$(PATH_FROM_SRC)/pngset.c\
$(PATH_FROM_SRC)/pngtrans.c\
$(PATH_FROM_SRC)/pngwio.c\
$(PATH_FROM_SRC)/pngwrite.c\
$(PATH_FROM_SRC)/pngwtran.c\
$(PATH_FROM_SRC)/pngwutil.c

include $(BUILD_STATIC_LIBRARY)
