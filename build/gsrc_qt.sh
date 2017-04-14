#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_BIN=${GX_ROOT}/bin
GX_TE=${GX_BIN}/gx_te

#core
${GX_TE} -i ${GX_ROOT}/core/project/qt/GXCore.pro -o ${GX_ROOT}/core/project/qt/GXCore.pro \
-fp "#__SOURCES_START__" -fs "#__SOURCES_END__" \
-fd ${GX_ROOT}/core/src \
-fe .cpp -fe .c \
-fsp "\t../../src" -fss "\\\n" \
-ff GJNI.cpp -ff GAndroidApp.cpp -ff GXCWnd.cpp \
-fsfp "\t#../../src" -fsfs "\\\n" \
-fi GXPthread.cpp

${GX_TE} -i ${GX_ROOT}/core/project/qt/GXCore.pro -o ${GX_ROOT}/core/project/qt/GXCore.pro \
-fp "#__HEADERS_START__" -fs "#__HEADERS_END__" \
-fd ${GX_ROOT}/core/src \
-fe .h \
-fsp "\t../../src" -fss "\\\n"

