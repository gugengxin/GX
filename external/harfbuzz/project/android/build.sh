#!/bin/sh

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD
cd $PROJECT_ROOT

source $GX_ROOT/bin/ndk.sh
source $GX_ROOT/bin/cmake.sh
source $GX_ROOT/bin/ninja.sh

SRC_ROOT=$LIBRARY_ROOT/src

OUTPUT_DIR=$LIBRARY_ROOT/lib/ard
if [ -d $OUTPUT_DIR ] 
then
rm -rf $OUTPUT_DIR
fi
mkdir -p $OUTPUT_DIR

TARGET_NAME=harfbuzz

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
	cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/android.toolchain.cmake" -D"CMAKE_ANDROID_NDK=${ANDROID_NDK_ROOT}" -D"CMAKE_ANDROID_ARCH_ABI=${ARCH_ABI}" -D"CMAKE_SYSTEM_VERSION=${API_LEVEL}" -D"HB_HAVE_FREETYPE=FALSE" -D"HB_HAVE_GLIB=FALSE" ${SRC_ROOT}
	ninja -C .
	mkdir -p $OUTPUT_DIR/${ARCH_ABI}
	mv lib${TARGET_NAME}.a $OUTPUT_DIR/${ARCH_ABI}/${TARGET_NAME}.a
	cd ..
done

cp $PROJECT_ROOT/libAndroid.mk $OUTPUT_DIR/Android.mk

cd $PROJECT_ROOT
rm -rf build

INCLUDE_DIR=${LIBRARY_ROOT}/include
if [ -d ${INCLUDE_DIR} ] 
then
rm -rf ${INCLUDE_DIR}
fi
mkdir -p ${INCLUDE_DIR}

cd ${SRC_ROOT}/src
find . -name "*.h" -depth 1 -exec cp {} ${INCLUDE_DIR}/{} \;





