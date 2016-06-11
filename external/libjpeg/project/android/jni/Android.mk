LOCAL_PATH := $(call my-dir)

PATH_FROM_SRC := ../../../src

include $(CLEAR_VARS)

LOCAL_MODULE    := jpeg
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../../include $(LOCAL_PATH)/../../../include/ard $(LOCAL_PATH)/../../../src
LOCAL_SRC_FILES := \
$(PATH_FROM_SRC)/jaricom.c\
$(PATH_FROM_SRC)/jcapimin.c\
$(PATH_FROM_SRC)/jcapistd.c\
$(PATH_FROM_SRC)/jcarith.c\
$(PATH_FROM_SRC)/jccoefct.c\
$(PATH_FROM_SRC)/jccolor.c\
$(PATH_FROM_SRC)/jcdctmgr.c\
$(PATH_FROM_SRC)/jchuff.c\
$(PATH_FROM_SRC)/jcinit.c\
$(PATH_FROM_SRC)/jcmainct.c\
$(PATH_FROM_SRC)/jcmarker.c\
$(PATH_FROM_SRC)/jcmaster.c\
$(PATH_FROM_SRC)/jcomapi.c\
$(PATH_FROM_SRC)/jcparam.c\
$(PATH_FROM_SRC)/jcprepct.c\
$(PATH_FROM_SRC)/jcsample.c\
$(PATH_FROM_SRC)/jctrans.c\
$(PATH_FROM_SRC)/jdapimin.c\
$(PATH_FROM_SRC)/jdapistd.c\
$(PATH_FROM_SRC)/jdarith.c\
$(PATH_FROM_SRC)/jdatadst.c\
$(PATH_FROM_SRC)/jdatasrc.c\
$(PATH_FROM_SRC)/jdcoefct.c\
$(PATH_FROM_SRC)/jdcolor.c\
$(PATH_FROM_SRC)/jddctmgr.c\
$(PATH_FROM_SRC)/jdhuff.c\
$(PATH_FROM_SRC)/jdinput.c\
$(PATH_FROM_SRC)/jdmainct.c\
$(PATH_FROM_SRC)/jdmarker.c\
$(PATH_FROM_SRC)/jdmaster.c\
$(PATH_FROM_SRC)/jdmerge.c\
$(PATH_FROM_SRC)/jdpostct.c\
$(PATH_FROM_SRC)/jdsample.c\
$(PATH_FROM_SRC)/jdtrans.c\
$(PATH_FROM_SRC)/jerror.c\
$(PATH_FROM_SRC)/jfdctflt.c\
$(PATH_FROM_SRC)/jfdctfst.c\
$(PATH_FROM_SRC)/jfdctint.c\
$(PATH_FROM_SRC)/jidctflt.c\
$(PATH_FROM_SRC)/jidctfst.c\
$(PATH_FROM_SRC)/jidctint.c\
$(PATH_FROM_SRC)/jquant1.c\
$(PATH_FROM_SRC)/jquant2.c\
$(PATH_FROM_SRC)/jutils.c\
$(PATH_FROM_SRC)/jmemmgr.c\
$(PATH_FROM_SRC)/jmemnobs.c\

include $(BUILD_STATIC_LIBRARY)
