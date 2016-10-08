#!/bin/sh

GX_CURRENT=$(pwd)
cd $(dirname "$0")/../../..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}
GX_BIN=${GX_ROOT}/bin

source $GX_BIN/qt.sh
source $GX_BIN/xcode.sh


PROJECT_DIRS=("text_editor" "sl" "uuid") 
PROJECT_NAMES=("gx_te" "gx_sl" "gx_uuid")

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
	qmake -makefile ${PROJECT_DIR}/${PROJECT_NAMES[$i]}.pro
	make
	cp ./${PROJECT_NAMES[$i]} ${GX_BIN}
	cd ${GX_CURRENT}
	rm -rf ${BUILD_DIR}

	#macdeployqt ${GX_BIN}/${PROJECT_NAMES[$i]}
done
