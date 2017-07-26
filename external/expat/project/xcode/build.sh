#!/bin/sh

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD
cd $PROJECT_ROOT

source $GX_ROOT/bin/xcode.sh
source $GX_ROOT/bin/cmake.sh
source $GX_ROOT/bin/ninja.sh

SRC_ROOT=${LIBRARY_ROOT}/src

mkdir build
cd build

mkdir ios
cd ios

mkdir device
cd device
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/ios.toolchain.cmake" -DIOS_PLATFORM="OS" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
ninja -C .

cd ..
mkdir simulator
cd simulator
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/ios.toolchain.cmake" -DIOS_PLATFORM="SIMULATOR" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
mv expat_config.h expat_config.old.h
cp ../device/expat_config.h .
ninja -C .

cd ..
mkdir simulator64
cd simulator64
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/ios.toolchain.cmake" -DIOS_PLATFORM="SIMULATOR64" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
mv expat_config.h expat_config.old.h
cp ../device/expat_config.h .
ninja -C .

cd $PROJECT_ROOT
cd build

mkdir atv
cd atv

mkdir device
cd device
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/appletv.toolchain.cmake" -DTVOS_PLATFORM="OS" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
ninja -C .

cd ..
mkdir simulator
cd simulator
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/appletv.toolchain.cmake" -DTVOS_PLATFORM="SIMULATOR" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
ninja -C .

cd $PROJECT_ROOT
cd build

mkdir mac
cd mac

cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/mac.toolchain.cmake" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_C_FLAGS="-DHAVE_ARC4RANDOM_BUF" ${SRC_ROOT}
ninja -C .

#输出文件
cd $PROJECT_ROOT

OUTPUT_DIR=$LIBRARY_ROOT/lib

if [ -d $OUTPUT_DIR/ios ] 
then
rm -rf $OUTPUT_DIR/ios
fi
mkdir -p $OUTPUT_DIR/ios

if [ -d $OUTPUT_DIR/atv ] 
then
rm -rf $OUTPUT_DIR/atv
fi
mkdir -p $OUTPUT_DIR/atv

if [ -d $OUTPUT_DIR/mac ] 
then
rm -rf $OUTPUT_DIR/mac
fi
mkdir -p $OUTPUT_DIR/mac

TARGET_NAME=expat

lipo -create build/ios/device/lib${TARGET_NAME}.a build/ios/simulator/lib${TARGET_NAME}.a build/ios/simulator64/lib${TARGET_NAME}.a -output $OUTPUT_DIR/ios/lib${TARGET_NAME}.a
lipo -create build/atv/device/lib${TARGET_NAME}.a build/atv/simulator/lib${TARGET_NAME}.a -output $OUTPUT_DIR/atv/lib${TARGET_NAME}.a
lipo -create build/mac/lib${TARGET_NAME}.a -output $OUTPUT_DIR/mac/lib${TARGET_NAME}.a


INCLUDE_DIR=$LIBRARY_ROOT/include

if [ -d $INCLUDE_DIR/ios ] 
then
rm -rf $INCLUDE_DIR/ios
fi
mkdir -p $INCLUDE_DIR/ios
cp build/ios/device/expat_config.h $INCLUDE_DIR/ios

if [ -d $INCLUDE_DIR/atv ] 
then
rm -rf $INCLUDE_DIR/atv
fi
mkdir -p $INCLUDE_DIR/atv
cp build/atv/device/expat_config.h $INCLUDE_DIR/atv

if [ -d $INCLUDE_DIR/mac ] 
then
rm -rf $INCLUDE_DIR/mac
fi
mkdir -p $INCLUDE_DIR/mac                       
cp build/mac/expat_config.h $INCLUDE_DIR/mac

cp ${SRC_ROOT}/lib/expat.h $INCLUDE_DIR
cp ${SRC_ROOT}/lib/expat_external.h $INCLUDE_DIR

rm -rf build



