#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

function XBuild {
	if [ ! -x $1 ]; then
  		chmod u+x $1
	fi

	$1
}

XBuild ${GX_ROOT}/tool/cmd/build/build_all.sh

XBuild ${GX_ROOT}/external/expat/project/xcode/build.sh
XBuild ${GX_ROOT}/external/expat/project/android/build.sh

XBuild ${GX_ROOT}/external/freetype/project/xcode/build.sh
XBuild ${GX_ROOT}/external/freetype/project/android/build.sh

XBuild ${GX_ROOT}/external/harfbuzz/project/xcode/build.sh
XBuild ${GX_ROOT}/external/harfbuzz/project/android/build.sh

XBuild ${GX_ROOT}/external/libjpeg/project/xcode/build.sh
XBuild ${GX_ROOT}/external/libjpeg/project/android/build.sh

XBuild ${GX_ROOT}/external/libpng/project/xcode/build.sh
XBuild ${GX_ROOT}/external/libpng/project/android/build.sh

XBuild ${GX_ROOT}/external/openal/project/android/build.sh

XBuild ${GX_ROOT}/external/zlib/project/xcode/build.sh
XBuild ${GX_ROOT}/external/zlib/project/android/build.sh