#!/bin/sh

echo "Setup NDK environment"

command -v ndk-build >/dev/null 2>&1 || {
	echo "Please input NDK path: "
	read GX_NDK_ROOT
	export PATH=$PATH:$GX_NDK_ROOT
}

if [ "${ANDROID_NDK_ROOT}" == "" ] 
then
	export ANDROID_NDK_ROOT=$(dirname $(which ndk-build))
	echo "ANDROID_NDK_ROOT=${ANDROID_NDK_ROOT}"
fi