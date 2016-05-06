#!/bin/sh


GX_CURRENT=$(pwd)
cd $(dirname "$0")/..
GX_ROOT=$(pwd)
cd ${GX_CURRENT}

GX_SRC=${GX_ROOT}/src

javac -d ${GX_SRC} ${GX_ROOT}/project/as/gx/src/main/java/com/gxengine/GX.java
javah -classpath ${GX_SRC} -d ${GX_SRC} -jni com.gxengine.GX

javac -d ${GX_SRC} ${GX_ROOT}/project/as/gx/src/main/java/com/gxengine/gx/GJavaJAPI.java
javah -classpath ${GX_SRC} -d ${GX_SRC} -jni com.gxengine.gx.GJavaJAPI

rm -rf ${GX_SRC}/com





