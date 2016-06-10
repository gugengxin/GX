#!/bin/sh

echo "Setup Qt environment"

command -v qmake >/dev/null 2>&1 || {
	echo "Please input Qt path: "
	read GX_QT_ROOT
	export PATH="$PATH:$GX_QT_ROOT/bin"
}