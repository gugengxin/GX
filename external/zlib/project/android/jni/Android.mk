LOCAL_PATH := $(call my-dir)

GX_PATH_FROM_SRC := ../../../src

include $(CLEAR_VARS)

LOCAL_MODULE    := gx_zlib
LOCAL_MODULE_FILENAME := zlib
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../../include
LOCAL_CFLAGS 	:= -DUSE_FILE32API -D_FILE_OFFSET_BITS=64
LOCAL_SRC_FILES := \
  $(GX_PATH_FROM_SRC)/adler32.c\
  $(GX_PATH_FROM_SRC)/crc32.c\
  $(GX_PATH_FROM_SRC)/deflate.c\
  $(GX_PATH_FROM_SRC)/infback.c\
  $(GX_PATH_FROM_SRC)/inffast.c\
  $(GX_PATH_FROM_SRC)/inflate.c\
  $(GX_PATH_FROM_SRC)/inftrees.c\
  $(GX_PATH_FROM_SRC)/trees.c\
  $(GX_PATH_FROM_SRC)/zutil.c\
  $(GX_PATH_FROM_SRC)/compress.c\
  $(GX_PATH_FROM_SRC)/uncompr.c\
  $(GX_PATH_FROM_SRC)/gzclose.c\
  $(GX_PATH_FROM_SRC)/gzlib.c\
  $(GX_PATH_FROM_SRC)/gzread.c\
  $(GX_PATH_FROM_SRC)/gzwrite.c\
  $(GX_PATH_FROM_SRC)/zip.c\
  $(GX_PATH_FROM_SRC)/unzip.c\
  $(GX_PATH_FROM_SRC)/ioapi.c\

  
include $(BUILD_STATIC_LIBRARY)
