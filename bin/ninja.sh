#!/bin/sh

echo "Setup Ninja environment"

command -v cmake >/dev/null 2>&1 || {
	echo "Please input Ninja path: "
	read GX_NINJA_ROOT
	export PATH=$PATH:$GX_NINJA_ROOT/bin
}