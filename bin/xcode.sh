#!/bin/sh

echo "Setup Xcode environment"

command -v xcodebuild >/dev/null 2>&1 || { 
	echo "Please input Xcode path: "
	read GX_XCODE_ROOT
	export PATH=$PATH:$GX_XCODE_ROOT/Contents/Developer/usr/bin
}