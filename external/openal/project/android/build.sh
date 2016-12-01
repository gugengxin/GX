#!/bin/sh

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD


SRC_ROOT=$LIBRARY_ROOT/src

if [ -d $SRC_ROOT/android ] 
then
rm -rf $SRC_ROOT/android
fi
mkdir -p $SRC_ROOT/android
cp -r $PROJECT_ROOT/jni $SRC_ROOT/android

source $GX_ROOT/bin/ndk.sh

ndk-build NDK_PROJECT_PATH=$SRC_ROOT/android

OUTPUT_DIR=$LIBRARY_ROOT/lib/ard
if [ -d $OUTPUT_DIR ] 
then
rm -rf $OUTPUT_DIR
fi
mkdir -p $OUTPUT_DIR

if [ -d $LIBRARY_ROOT/include ] 
then
rm -rf $LIBRARY_ROOT/include
fi

function move_lib {
	TEMP_OUT_DIR=$2/$(basename $(dirname $1))
	if [ ! -d $TEMP_OUT_DIR ] 
	then
		mkdir $TEMP_OUT_DIR
	fi
	mv $1 $TEMP_OUT_DIR
}
export -f move_lib
find $SRC_ROOT/android/obj/local -name "*.a" -exec bash -c "move_lib {} $OUTPUT_DIR" \;

cp -r $SRC_ROOT/include $LIBRARY_ROOT

rm -rf $SRC_ROOT/android
cp $PROJECT_ROOT/libAndroid.mk $OUTPUT_DIR/Android.mk



