#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_BIN=${GX_ROOT}/bin
GX_SL=${GX_BIN}/gx_sl

${GX_SL} -i ${GX_ROOT}/src/GSRGraphics.cpp -o ${GX_ROOT}/src/GSRGraphics.gxsl
${GX_SL} -i ${GX_ROOT}/src/GSRTexture2D.cpp -o ${GX_ROOT}/src/GSRTexture2D.gxsl