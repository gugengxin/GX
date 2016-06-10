#!/bin/sh

echo "Setup NDK environment"

command -v ndk-build >/dev/null 2>&1 || {
	echo "Please input NDK path: "
	read GX_NDK_ROOT
	export PATH=$PATH:$GX_NDK_ROOT
}