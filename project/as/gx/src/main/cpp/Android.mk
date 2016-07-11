LOCAL_PATH := $(call my-dir)

ENGINE_PATH := $(LOCAL_PATH)/../../../../../..
ENGINE_PATH_FROM_SRC := ../../../../../..

$(call import-add-path,$(LOCAL_PATH))
$(call import-add-path,$(ENGINE_PATH))

include $(CLEAR_VARS)

LOCAL_MODULE    := GX
LOCAL_C_INCLUDES:= $(ENGINE_PATH)/src
LOCAL_EXPORT_C_INCLUDES:= $(ENGINE_PATH)/src
LOCAL_CFLAGS 	+= -Wno-multichar -D GX_OS_ANDROID #-fvisibility=hidden
LOCAL_CPPFLAGS	+= -fno-rtti #-std=c++11 -fvisibility=hidden
ifdef NDK_DEBUG
   ifeq ($(NDK_DEBUG),1)
      CFLAGS		+= -O0 -g
      LOCAL_CFLAGS	+=-D DEBUG
      APP_OPTIM 	:= debug
   else
      CFLAGS		+= -O2 -g
      LOCAL_CFLAGS	+=-D NDEBUG
      APP_OPTIM 	:= release
  endif
endif
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS)
LOCAL_WHOLE_STATIC_LIBRARIES := GXAndroid 
LOCAL_STATIC_LIBRARIES	:= zlib
#LOCAL_LDLIBS 	:=
LOCAL_EXPORT_LDLIBS := -lEGL -lGLESv2 -llog -landroid -lOpenSLES
LOCAL_SRC_FILES := \
 $(ENGINE_PATH_FROM_SRC)/src/GAction.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GAppBundle.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GApplication.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GArray.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GAutoreleasePool.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GBuffer.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GBundle.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GClass.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GColor.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GCondition.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GContext.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GD3DContext.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GData.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GDataArray.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GDataBuffer.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GDataList.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GDataReader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GDataString.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GDShader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GFileReader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GFileBundle.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GFileManager.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GFileWriter.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/glew.c \
 $(ENGINE_PATH_FROM_SRC)/src/GList.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GLog.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GMap.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GMatrix.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GMutex.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GNotice.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GNoticeCenter.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GNumber.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GObject.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GOGLContext.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GOShader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GOWHash.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GPainter.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GPieceData.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GPtr.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GReader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GRunLoop.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GShader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GSRGraphics.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GString.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GSystem.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GTexture.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GTexture2D.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GThread.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GTString.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GUUID.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GVector.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GWindow.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GWriter.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GWString.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GXCWnd.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GXDirectX.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GXMath.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GXOpenGL.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GXPthread.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GZipBundle.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GZipReader.cpp \
 $(ENGINE_PATH_FROM_SRC)/src/GZipWriter.cpp \

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android)
$(call import-module,external/zlib/lib/ard)


