#!/bin/sh

if [ "$1" = "" ] || [ "$2" = "" ] || [ "$3" = "" ]
then
	echo "Help: +component name +object-name +object-base-name"
	exit
fi

GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}
TEMPLATES_PATH=$(dirname "$0")/templates

COMPONTENT="$1"
GX_BIN=${GX_ROOT}/bin
GX_TE=${GX_BIN}/gx_te
GX_SRC=${GX_ROOT}/${COMPONTENT}/src


S_OBJECTNAME="___OBJECTNAME___"
S_OBJECT_BASENAME="___OBJECT_BASENAME___"
D_OBJECTNAME="$2"
D_OBJECT_BASENAME="$3"

$GX_TE -i ${TEMPLATES_PATH}/___GObject___.h -o ${GX_SRC}/${D_OBJECTNAME}.h -rs "${S_OBJECTNAME}" 		-rd "${D_OBJECTNAME}"
$GX_TE -i ${GX_SRC}/${D_OBJECTNAME}.h 		-o ${GX_SRC}/${D_OBJECTNAME}.h -rs "${S_OBJECT_BASENAME}" 	-rd "${D_OBJECT_BASENAME}"

$GX_TE -i ${TEMPLATES_PATH}/___GObject___.cpp 	-o ${GX_SRC}/${D_OBJECTNAME}.cpp -rs "${S_OBJECTNAME}" 		-rd "${D_OBJECTNAME}"
$GX_TE -i ${GX_SRC}/${D_OBJECTNAME}.cpp 		-o ${GX_SRC}/${D_OBJECTNAME}.cpp -rs "${S_OBJECT_BASENAME}" -rd "${D_OBJECT_BASENAME}"