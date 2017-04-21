LOCAL_PATH := $(call my-dir)

ENGINE_PATH := $(LOCAL_PATH)/../../../../../../../..
$(call import-add-path,$(ENGINE_PATH))

SHARED_PATH := $(LOCAL_PATH)/../../../../../../src
SHARED_PATH_FROM_SRC := ../../../../../../src

include $(CLEAR_VARS)

LOCAL_MODULE := GXGameTest
LOCAL_STATIC_LIBRARIES := GXCore GXGame
LOCAL_C_INCLUDES += $(SHARED_PATH)
LOCAL_SRC_FILES := \
 $(SHARED_PATH_FROM_SRC)/AppDge.cpp\
 $(SHARED_PATH_FROM_SRC)/Game.cpp

include $(BUILD_SHARED_LIBRARY)

$(call import-module,core/project/as/gxcore/src/main/cpp)
$(call import-module,game/project/as/gxgame/src/main/cpp)
