#!/bin/sh

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD
cd $PROJECT_ROOT

source $GX_ROOT/bin/xcode.sh

xcodebuild -project zlib.xcodeproj -target zlib_ios -configuration Release -sdk iphoneos build
xcodebuild -project zlib.xcodeproj -target zlib_ios -configuration Release -sdk iphonesimulator build
xcodebuild -project zlib.xcodeproj -target zlib_atv -configuration Release -sdk appletvos build
xcodebuild -project zlib.xcodeproj -target zlib_atv -configuration Release -sdk appletvsimulator build
xcodebuild -project zlib.xcodeproj -target zlib_mac -configuration Release -sdk macosx build

OUTPUT_DIR=$LIBRARY_ROOT/lib
if [ -d $OUTPUT_DIR ] 
then
rm -rf $OUTPUT_DIR
fi
mkdir -p $OUTPUT_DIR/ios
mkdir -p $OUTPUT_DIR/atv
mkdir -p $OUTPUT_DIR/mac

lipo -create build/Release-iphoneos/zlib.a build/Release-iphonesimulator/zlib.a -output $OUTPUT_DIR/ios/zlib.a
lipo -create build/Release-appletvos/zlib.a build/Release-appletvsimulator/zlib.a -output $OUTPUT_DIR/atv/zlib.a
lipo -create build/Release/zlib.a -output $OUTPUT_DIR/mac/zlib.a
                       
rm -rf build





