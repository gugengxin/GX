#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_BIN=${GX_ROOT}/bin
GX_TE=${GX_BIN}/gx_te

${GX_TE} -i ${GX_ROOT}/project/as/gx/src/main/cpp/Android.mk \
-o ${GX_ROOT}/project/as/gx/src/main/cpp/Android.mk \
-fp "#__LOCAL_SRC_FILES_START__" -fs "#__LOCAL_SRC_FILES_END__" \
-fd ${GX_ROOT}/src \
-fe .cpp -fe .c \
-fsp "LOCAL_SRC_FILES += \$(ENGINE_PATH_FROM_SRC)/src" -fss "\n" \
-fi GJNI.cpp -fi GAndroid.cpp -fi GAndroidC.cpp -fi GAndroidJ.cpp

