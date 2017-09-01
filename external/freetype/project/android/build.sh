#!/bin/sh
set -e

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD
cd $PROJECT_ROOT

SRC_ROOT=$LIBRARY_ROOT/src

source $GX_ROOT/bin/cmake.sh
source $GX_ROOT/bin/ninja.sh
source $GX_ROOT/bin/ndk.sh

function copyInclude {
	OUTPUT_H_DIR="$1"
	CMAKE_CACHE_DIR="$2"
	if [ -d $OUTPUT_H_DIR ]; then
		rm -rf $OUTPUT_H_DIR
	fi
	cp -r ${SRC_ROOT}/include $OUTPUT_H_DIR
	cp -f ${CMAKE_CACHE_DIR}/include/freetype/config/ftconfig.h $OUTPUT_H_DIR/freetype/config/ftconfig.h
	cp -f ${CMAKE_CACHE_DIR}/include/freetype/config/ftoption.h $OUTPUT_H_DIR/freetype/config/ftoption.h
}

OUTPUT_DIR=$LIBRARY_ROOT/lib/ard
if [ -d $OUTPUT_DIR ] 
then
rm -rf $OUTPUT_DIR
fi
mkdir -p $OUTPUT_DIR

TARGET_NAME=freetype

mkdir build
cd build

ARCH_ABIs=("armeabi" "armeabi-v7a" "arm64-v8a" "x86" "x86_64" "mips" "mips64")
for ((i=0;i<${#ARCH_ABIs[@]};i++))
do
	ARCH_ABI=${ARCH_ABIs[$i]}
	if [ ${ARCH_ABI} == "arm64-v8a" ] || [ ${ARCH_ABI} == "x86_64" ] || [ ${ARCH_ABI} == "mips64" ]
	then
		API_LEVEL=21
	else
		API_LEVEL=14
	fi
	mkdir ${ARCH_ABI}
	cd ${ARCH_ABI}
	cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/android.toolchain.cmake" -D"CMAKE_ANDROID_NDK=${ANDROID_NDK_ROOT}" -D"CMAKE_ANDROID_ARCH_ABI=${ARCH_ABI}" -D"CMAKE_SYSTEM_VERSION=${API_LEVEL}" -D"CMAKE_BUILD_TYPE=Release" -D"FREETYPE_NO_DIST=true" -D"WITH_ZLIB=OFF" -D"WITH_BZip2=OFF" -D"WITH_PNG=OFF" -D"WITH_HarfBuzz=OFF" ${SRC_ROOT}
	ninja -C .
	mkdir -p $OUTPUT_DIR/${ARCH_ABI}
	mv lib${TARGET_NAME}.a $OUTPUT_DIR/${ARCH_ABI}/lib${TARGET_NAME}.a
	cd ..
done

cd ..

cp $PROJECT_ROOT/libAndroid.mk $OUTPUT_DIR/Android.mk

copyInclude $LIBRARY_ROOT/include/ard $PROJECT_ROOT/build/armeabi

rm -rf build





