LOCAL_PATH := $(call my-dir)

PATH_FROM_SRC := ../../../src

include $(CLEAR_VARS)

LOCAL_MODULE    := freetype
LOCAL_CFLAGS +=  -D__LINUX_CPL__ -DUNICODE -DFT2_BUILD_LIBRARY
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../../include $(LOCAL_PATH)/../../../src
LOCAL_SRC_FILES := $(PATH_FROM_SRC)/base/ftsystem.c \
      $(PATH_FROM_SRC)/base/ftinit.c \
      $(PATH_FROM_SRC)/base/ftdebug.c \
      $(PATH_FROM_SRC)/base/ftbase.c \
      $(PATH_FROM_SRC)/base/ftbbox.c \
      $(PATH_FROM_SRC)/base/ftglyph.c \
      $(PATH_FROM_SRC)/base/ftbdf.c \
      $(PATH_FROM_SRC)/base/ftbitmap.c \
      $(PATH_FROM_SRC)/base/ftcid.c \
      $(PATH_FROM_SRC)/base/ftfstype.c \
      $(PATH_FROM_SRC)/base/ftgasp.c \
      $(PATH_FROM_SRC)/base/ftgxval.c \
      $(PATH_FROM_SRC)/base/ftlcdfil.c \
      $(PATH_FROM_SRC)/base/ftmm.c \
      $(PATH_FROM_SRC)/base/ftotval.c \
      $(PATH_FROM_SRC)/base/ftpatent.c \
      $(PATH_FROM_SRC)/base/ftpfr.c \
      $(PATH_FROM_SRC)/base/ftstroke.c \
      $(PATH_FROM_SRC)/base/ftsynth.c \
      $(PATH_FROM_SRC)/base/fttype1.c \
      $(PATH_FROM_SRC)/base/ftwinfnt.c \
      $(PATH_FROM_SRC)/base/ftxf86.c
#      $(PATH_FROM_SRC)/base/ftmac.c

LOCAL_SRC_FILES += $(PATH_FROM_SRC)/bdf/bdf.c \
      $(PATH_FROM_SRC)/cff/cff.c \
      $(PATH_FROM_SRC)/cid/type1cid.c \
      $(PATH_FROM_SRC)/pcf/pcf.c \
      $(PATH_FROM_SRC)/pfr/pfr.c \
      $(PATH_FROM_SRC)/sfnt/sfnt.c \
      $(PATH_FROM_SRC)/truetype/truetype.c \
      $(PATH_FROM_SRC)/type1/type1.c \
      $(PATH_FROM_SRC)/type42/type42.c \
      $(PATH_FROM_SRC)/winfonts/winfnt.c \
      
LOCAL_SRC_FILES += $(PATH_FROM_SRC)/raster/raster.c \
      $(PATH_FROM_SRC)/smooth/smooth.c
      
LOCAL_SRC_FILES += $(PATH_FROM_SRC)/autofit/autofit.c \
      $(PATH_FROM_SRC)/cache/ftcache.c \
      $(PATH_FROM_SRC)/gzip/ftgzip.c \
      $(PATH_FROM_SRC)/lzw/ftlzw.c \
      $(PATH_FROM_SRC)/gxvalid/gxvalid.c \
      $(PATH_FROM_SRC)/otvalid/otvalid.c \
      $(PATH_FROM_SRC)/psaux/psaux.c \
      $(PATH_FROM_SRC)/pshinter/pshinter.c \
      $(PATH_FROM_SRC)/psnames/psnames.c
      
LOCAL_CFLAGS    +=  \
 -I$(LOCAL_PATH)/../../../src/autofit/ \
 -I$(LOCAL_PATH)/../../../src/base/ \
 -I$(LOCAL_PATH)/../../../src/bdf/ \
 -I$(LOCAL_PATH)/../../../src/cff/ \
 -I$(LOCAL_PATH)/../../../src/cid/ \
 -I$(LOCAL_PATH)/../../../src/gxvalid/ \
 -I$(LOCAL_PATH)/../../../src/gzip/ \
 -I$(LOCAL_PATH)/../../../src/lzw/ \
 -I$(LOCAL_PATH)/../../../src/otvalid/ \
 -I$(LOCAL_PATH)/../../../src/pcf/ \
 -I$(LOCAL_PATH)/../../../src/pfr/ \
 -I$(LOCAL_PATH)/../../../src/psaux/ \
 -I$(LOCAL_PATH)/../../../src/pshinter/ \
 -I$(LOCAL_PATH)/../../../src/psnames/ \
 -I$(LOCAL_PATH)/../../../src/raster/ \
 -I$(LOCAL_PATH)/../../../src/sfnt/ \
 -I$(LOCAL_PATH)/../../../src/smooth/ \
 -I$(LOCAL_PATH)/../../../src/tools/ \
 -I$(LOCAL_PATH)/../../../src/tools/docmaker/ \
 -I$(LOCAL_PATH)/../../../src/tools/ftrandom/ \
 -I$(LOCAL_PATH)/../../../src/truetype/ \
 -I$(LOCAL_PATH)/../../../src/type1/ \
 -I$(LOCAL_PATH)/../../../src/type42/ \
 -I$(LOCAL_PATH)/../../../src/winfonts/ \
 -I$(LOCAL_PATH)/../../../include/ \
 -I$(LOCAL_PATH)/../../../include/freetype/ \
 -I$(LOCAL_PATH)/../../../include/freetype/config/ \
 -I$(LOCAL_PATH)/../../../include/freetype/internal/ \
 -I$(LOCAL_PATH)/../../../include/freetype/internal/services/ 

include $(BUILD_STATIC_LIBRARY)
