#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_BIN=${GX_ROOT}/bin
GX_TE=${GX_BIN}/gx_te

#core
${GX_TE} -i ${GX_ROOT}/core/project/as/gxcore/src/main/cpp/Android.mk \
-o ${GX_ROOT}/core/project/as/gxcore/src/main/cpp/Android.mk \
-fp "#__LOCAL_SRC_FILES_START__" -fs "#__LOCAL_SRC_FILES_END__" \
-fd ${GX_ROOT}/core/src \
-fe .cpp -fe .c \
-fsp "LOCAL_SRC_FILES += \$(ENGINE_PATH_FROM_SRC)/core/src" -fss "\n" \
-fi GJNI.cpp -fi GAndroidApp.cpp

