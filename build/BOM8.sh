#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_BIN=${GX_ROOT}/bin
GX_TE=${GX_BIN}/gx_te

find ${GX_ROOT}/core/src \( -name "*.h" -o -name "*.cpp" -o -name "*.c" \) -print -exec ${GX_TE} -i {} -o {} -oe UTF-8 -oebom8 1 \;
find ${GX_ROOT}/core/test/src \( -name "*.h" -o -name "*.cpp" -o -name "*.c" \) -print -exec ${GX_TE} -i {} -o {} -oe UTF-8 -oebom8 1 \;
find ${GX_ROOT}/game/src \( -name "*.h" -o -name "*.cpp" -o -name "*.c" \) -print -exec ${GX_TE} -i {} -o {} -oe UTF-8 -oebom8 1 \;
find ${GX_ROOT}/game/test/src \( -name "*.h" -o -name "*.cpp" -o -name "*.c" \) -print -exec ${GX_TE} -i {} -o {} -oe UTF-8 -oebom8 1 \;
find ${GX_ROOT}/tool/cmd/shared_src \( -name "*.h" -o -name "*.cpp" -o -name "*.c" \) -print -exec ${GX_TE} -i {} -o {} -oe UTF-8 -oebom8 1 \;


