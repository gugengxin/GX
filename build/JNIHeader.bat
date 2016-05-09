@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_SRC=%GX_ROOT%\src

javac -d %GX_SRC% %GX_ROOT%\project\as\gx\src\main\java\com\gxengine\GX.java
javah -classpath %GX_SRC% -d %GX_SRC% -jni com.gxengine.GX

javac -d %GX_SRC% %GX_ROOT%\project\as\gx\src\main\java\com\gxengine\gx\GJavaJAPI.java
javah -classpath %GX_SRC% -d %GX_SRC% -jni com.gxengine.gx.GJavaJAPI

rd /s /q %GX_SRC%\com

pause