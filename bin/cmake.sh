#!/bin/sh

echo "Setup CMake environment"

command -v cmake >/dev/null 2>&1 || {
	echo "Please input CMake path: "
	read GX_CMAKE_ROOT
	export PATH=$PATH:$GX_CMAKE_ROOT/bin
}