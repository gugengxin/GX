LOCAL_PATH := $(call my-dir)

ENGINE_PATH := $(LOCAL_PATH)/../../../../../../..
ENGINE_PATH_FROM_SRC := ../../../../../../..

$(call import-add-path,$(ENGINE_PATH))

#Android与系统交互部分
include $(CLEAR_VARS)
LOCAL_MODULE    := GXGameAndroid
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/core/src $(ENGINE_PATH)/game/src
LOCAL_CFLAGS 	+= -Wno-multichar
LOCAL_CPPFLAGS	+= -fno-rtti
LOCAL_SRC_FILES := \
    $(ENGINE_PATH_FROM_SRC)/game/src/GAndroidEntrance.cpp\
    $(ENGINE_PATH_FROM_SRC)/game/src/GAndroidActivity.cpp\
    $(ENGINE_PATH_FROM_SRC)/game/src/GAndroidDaydream.cpp

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := GXGame
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/core/src $(ENGINE_PATH)/game/src
LOCAL_EXPORT_C_INCLUDES:= $(ENGINE_PATH)/game/src
LOCAL_CFLAGS 	+= -Wno-multichar
LOCAL_CPPFLAGS	+= -fno-rtti
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS)
LOCAL_WHOLE_STATIC_LIBRARIES := GXGameAndroid
#LOCAL_STATIC_LIBRARIES	:=
#LOCAL_LDLIBS 	:=
LOCAL_EXPORT_LDLIBS := -lEGL -lGLESv2 -lOpenSLES
#__LOCAL_SRC_FILES_START__
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GBaseContext.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GBuffer.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GCanvas.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GContext.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GD3DContext.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GDShader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GFrameBuffer.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GGame.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GGameResManager.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GIndexBuffer.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GMShader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GMTLContext.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GOGLContext.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GOShader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GSRGraphics.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GSRTexture2D.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GShader.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GTex2DFont.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GTexture.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GTexture1D.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GTexture2D.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GTextureCube.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GWindow.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GX3DAPI.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GXDirectX.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GXMetal.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/GXOpenGL.cpp
LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src/glew.c
#__LOCAL_SRC_FILES_END__

include $(BUILD_STATIC_LIBRARY)


