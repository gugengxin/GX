#!/bin/sh

command -v qmake >/dev/null 2>&1 || { 
	echo "Can't find qmake,please input Qt SDK path:"
	read GX_QT_SDK
	export PATH=$PATH:$GX_QT_SDK/bin
}

command -v make >/dev/null 2>&1 || { 
	echo "Can't find make,please install the xcode."
	exit
}


GX_QMAKE=qmake
GX_CURRENT=$(pwd)
cd $(dirname "$0")/../../..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}
GX_BIN=${GX_ROOT}/bin

PROJECT_DIRS=("text_editor" "sl") 
PROJECT_NAMES=("gx_te" "gx_sl")

for ((i=0;i<${#PROJECT_DIRS[@]};i++))
do
	ROOT_DIR=${GX_ROOT}/tool/cmd/${PROJECT_DIRS[$i]}
	PROJECT_DIR=${ROOT_DIR}/project/qt
	BUILD_DIR=${PROJECT_DIR}/build

	if [ -d ${BUILD_DIR} ]; then
  		rm -rf ${BUILD_DIR}
	fi
	mkdir ${BUILD_DIR}

	cd ${BUILD_DIR}
	${GX_QMAKE} -makefile ${PROJECT_DIR}/${PROJECT_NAMES[$i]}.pro
	make
	cp ./${PROJECT_NAMES[$i]} ${GX_BIN}
	cd ${GX_CURRENT}
	rm -rf ${BUILD_DIR}

	#macdeployqt ${GX_BIN}/${PROJECT_NAMES[$i]}
done
