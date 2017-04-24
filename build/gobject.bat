@echo off

if "%3"=="" (
	echo Help: +component-name +object-name +object-base-name
	goto :EOF
)

pushd %~dp0\..
set GX_ROOT=%cd%
popd
pushd %~dp0
set TEMPLATES_PATH=%cd%/templates
popd

set COMPONTENT=%1
set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe
set GX_SRC=%GX_ROOT%\%COMPONTENT%\src

set S_OBJECTNAME=___OBJECTNAME___
set S_OBJECT_BASENAME=___OBJECT_BASENAME___
set D_OBJECTNAME=%2
set D_OBJECT_BASENAME=%3

%GX_TE% -i %TEMPLATES_PATH%\___GObject___.h 	-o %GX_SRC%\%D_OBJECTNAME%.h 	-rs "%S_OBJECTNAME%" 		-rd "%D_OBJECTNAME%"
%GX_TE% -i %GX_SRC%\%D_OBJECTNAME%.h 			-o %GX_SRC%\%D_OBJECTNAME%.h 	-rs "%S_OBJECT_BASENAME%" 	-rd "%D_OBJECT_BASENAME%"

%GX_TE% -i %TEMPLATES_PATH%\___GObject___.cpp 	-o %GX_SRC%\%D_OBJECTNAME%.cpp 	-rs "%S_OBJECTNAME%" 		-rd "%D_OBJECTNAME%"
%GX_TE% -i %GX_SRC%\%D_OBJECTNAME%.cpp 			-o %GX_SRC%\%D_OBJECTNAME%.cpp 	-rs "%S_OBJECT_BASENAME%" 	-rd "%D_OBJECT_BASENAME%"

goto :EOF
