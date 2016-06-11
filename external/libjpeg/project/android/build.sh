#!/bin/sh

cd $(dirname $0)
PROJECT_ROOT=$PWD
cd ../..
LIBRARY_ROOT=$PWD
cd ../..
GX_ROOT=$PWD

source $GX_ROOT/bin/ndk.sh

ndk-build NDK_PROJECT_PATH=$PROJECT_ROOT

OUTPUT_DIR=$LIBRARY_ROOT/lib/ard
if [ -d $OUTPUT_DIR ] 
then
rm -rf $OUTPUT_DIR
fi
mkdir -p $OUTPUT_DIR

function move_lib {
	TEMP_OUT_DIR=$2/$(basename $(dirname $1))
	if [ ! -d $TEMP_OUT_DIR ] 
	then
		mkdir $TEMP_OUT_DIR
	fi
	mv $1 $TEMP_OUT_DIR
}
export -f move_lib
find $PROJECT_ROOT/obj/local -name "*.a" -exec bash -c "move_lib {} $OUTPUT_DIR" \;

rm -rf $PROJECT_ROOT/obj
cp $PROJECT_ROOT/libAndroid.mk $OUTPUT_DIR/Android.mk



