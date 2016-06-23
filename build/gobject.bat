@echo off

if "%2"=="" (
	echo Help: +object-name +object-base-name
	goto :EOF
)

pushd %~dp0\..
set GX_ROOT=%cd%
popd
pushd %~dp0
set TEMPLATES_PATH=%cd%\templates
popd


set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe
set GX_SRC=%GX_ROOT%\src

set S_OBJECTNAME=___OBJECTNAME___
set S_OBJECT_BASENAME=___OBJECT_BASENAME___
set D_OBJECTNAME=%1
set D_OBJECT_BASENAME=%2

%GX_TE% -i %TEMPLATES_PATH%\___GObject___.h 	-o %GX_SRC%\%D_OBJECTNAME%.h 	-rs "%S_OBJECTNAME%" 		-rd "%D_OBJECTNAME%"
%GX_TE% -i %GX_SRC%\%D_OBJECTNAME%.h 			-o %GX_SRC%\%D_OBJECTNAME%.h 	-rs "%S_OBJECT_BASENAME%" 	-rd "%D_OBJECT_BASENAME%"

%GX_TE% -i %TEMPLATES_PATH%\___GObject___.cpp 	-o %GX_SRC%\%D_OBJECTNAME%.cpp 	-rs "%S_OBJECTNAME%" 		-rd "%D_OBJECTNAME%"
%GX_TE% -i %GX_SRC%\%D_OBJECTNAME%.cpp 			-o %GX_SRC%\%D_OBJECTNAME%.cpp 	-rs "%S_OBJECT_BASENAME%" 	-rd "%D_OBJECT_BASENAME%"

goto :EOF
