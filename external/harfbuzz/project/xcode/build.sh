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
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/ios.toolchain.cmake" -D"HB_HAVE_CORETEXT=FALSE" ${SRC_ROOT}
ninja -C .

cd ..
mkdir simulator
cd simulator
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/ios.toolchain.cmake" -D"HB_HAVE_CORETEXT=FALSE" -DIOS_PLATFORM="SIMULATOR" ${SRC_ROOT}
ninja -C .

cd ..
mkdir simulator64
cd simulator64
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/ios.toolchain.cmake" -D"HB_HAVE_CORETEXT=FALSE" -DIOS_PLATFORM="SIMULATOR64" ${SRC_ROOT}
ninja -C .

cd $PROJECT_ROOT
cd build

mkdir atv
cd atv

mkdir device
cd device
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/appletv.toolchain.cmake" -D"HB_HAVE_CORETEXT=FALSE" ${SRC_ROOT}
ninja -C .

cd ..
mkdir simulator
cd simulator
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/appletv.toolchain.cmake" -D"HB_HAVE_CORETEXT=FALSE" -DTVOS_PLATFORM="SIMULATOR" ${SRC_ROOT}
ninja -C .

cd $PROJECT_ROOT
cd build

mkdir mac
cd mac

export 
cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=${GX_ROOT}/bin/mac.toolchain.cmake" -D"HB_HAVE_CORETEXT=FALSE" ${SRC_ROOT}
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

TARGET_NAME=harfbuzz

lipo -create build/ios/device/lib${TARGET_NAME}.a build/ios/simulator/lib${TARGET_NAME}.a build/ios/simulator64/lib${TARGET_NAME}.a -output $OUTPUT_DIR/ios/lib${TARGET_NAME}.a
lipo -create build/atv/device/lib${TARGET_NAME}.a build/atv/simulator/lib${TARGET_NAME}.a -output $OUTPUT_DIR/atv/lib${TARGET_NAME}.a
lipo -create build/mac/lib${TARGET_NAME}.a -output $OUTPUT_DIR/mac/lib${TARGET_NAME}.a
                       
rm -rf build

INCLUDE_DIR=${LIBRARY_ROOT}/include
if [ -d ${INCLUDE_DIR} ] 
then
rm -rf ${INCLUDE_DIR}
fi
mkdir -p ${INCLUDE_DIR}

cd ${SRC_ROOT}/src
find . -name "*.h" -depth 1 -exec cp {} ${INCLUDE_DIR}/{} \;
find . -name "*.hh" -depth 1 -exec cp {} ${INCLUDE_DIR}/{} \;
















