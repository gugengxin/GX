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

INCLUDE_DIR=$LIBRARY_ROOT/include
OUTPUT_H_DIR=$INCLUDE_DIR/ard
if [ -d $OUTPUT_H_DIR ] 
then
rm -rf $OUTPUT_H_DIR
fi
mkdir -p $OUTPUT_H_DIR


TARGET_NAME=expat

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
	cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/android.toolchain.cmake" -D"CMAKE_ANDROID_NDK=${ANDROID_NDK_ROOT}" -D"CMAKE_ANDROID_ARCH_ABI=${ARCH_ABI}" -D"CMAKE_SYSTEM_VERSION=${API_LEVEL}" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
	ninja -C .
	mkdir -p $OUTPUT_DIR/${ARCH_ABI}
	mv lib${TARGET_NAME}.a $OUTPUT_DIR/${ARCH_ABI}/lib${TARGET_NAME}.a
	mkdir -p $OUTPUT_H_DIR/${ARCH_ABI}
	mv expat_config.h $OUTPUT_H_DIR/${ARCH_ABI}
	cd ..
done

cp $PROJECT_ROOT/libAndroid.mk $OUTPUT_DIR/Android.mk

cp ${SRC_ROOT}/lib/expat.h $INCLUDE_DIR
cp ${SRC_ROOT}/lib/expat_external.h $INCLUDE_DIR


cd $PROJECT_ROOT
rm -rf build







