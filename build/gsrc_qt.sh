#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_BIN=${GX_ROOT}/bin
GX_TE=${GX_BIN}/gx_te

${GX_TE} -i ${GX_ROOT}/project/qt/GX.pro -o ${GX_ROOT}/project/qt/GX.pro \
-fp "#__SOURCES_START__" -fs "#__SOURCES_END__" \
-fd ${GX_ROOT}/src \
-fe .cpp -fe .c \
-fsp "\t../../src" -fss "\\\n" \
-ff GBuffer.cpp -ff GD3DContext.cpp -ff GDShader.cpp -ff GJavaAPI.cpp -ff GJavaCAPI.cpp -ff GJavaJAPI.cpp -ff glew.c -ff GXCWnd.cpp -ff GXDirectX.cpp \
-fsfp "\t#../../src" -fsfs "\\\n" \
-fi GXPthread.cpp

${GX_TE} -i ${GX_ROOT}/project/qt/GX.pro -o ${GX_ROOT}/project/qt/GX.pro \
-fp "#__HEADERS_START__" -fs "#__HEADERS_END__" \
-fd ${GX_ROOT}/src \
-fe .h \
-fsp "\t../../src" -fss "\\\n"

