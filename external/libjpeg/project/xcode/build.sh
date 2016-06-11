#!/bin/sh

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD
cd $PROJECT_ROOT

source $GX_ROOT/bin/xcode.sh

TARGET_NAME=libjpeg

xcodebuild -project ${TARGET_NAME}.xcodeproj -target ${TARGET_NAME}_ios -configuration Release -sdk iphoneos build
xcodebuild -project ${TARGET_NAME}.xcodeproj -target ${TARGET_NAME}_ios -configuration Release -sdk iphonesimulator build
xcodebuild -project ${TARGET_NAME}.xcodeproj -target ${TARGET_NAME}_atv -configuration Release -sdk appletvos build
xcodebuild -project ${TARGET_NAME}.xcodeproj -target ${TARGET_NAME}_atv -configuration Release -sdk appletvsimulator build
xcodebuild -project ${TARGET_NAME}.xcodeproj -target ${TARGET_NAME}_mac -configuration Release -sdk macosx build

OUTPUT_DIR=$LIBRARY_ROOT/lib
if [ -d $OUTPUT_DIR ] 
then
rm -rf $OUTPUT_DIR
fi
mkdir -p $OUTPUT_DIR/ios
mkdir -p $OUTPUT_DIR/atv
mkdir -p $OUTPUT_DIR/mac

lipo -create build/Release-iphoneos/${TARGET_NAME}.a build/Release-iphonesimulator/${TARGET_NAME}.a -output $OUTPUT_DIR/ios/${TARGET_NAME}.a
lipo -create build/Release-appletvos/${TARGET_NAME}.a build/Release-appletvsimulator/${TARGET_NAME}.a -output $OUTPUT_DIR/atv/${TARGET_NAME}.a
lipo -create build/Release/${TARGET_NAME}.a -output $OUTPUT_DIR/mac/${TARGET_NAME}.a
                       
rm -rf build





