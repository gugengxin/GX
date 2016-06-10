@echo off

pushd %~dp0
set PROJECT_ROOT=%cd%
popd
pushd %PROJECT_ROOT%\..\..
set LIBRARY_ROOT=%cd%
popd
pushd %LIBRARY_ROOT%\..\..
set GX_ROOT=%cd%
popd

set OUTPUT_DIR=%LIBRARY_ROOT%\lib\ard

if exist %OUTPUT_DIR% (
	rd /s/q %OUTPUT_DIR%
)
mkdir %OUTPUT_DIR%

call %GX_ROOT%\bin\ndk.bat

call ndk-build.cmd NDK_PROJECT_PATH=%PROJECT_ROOT%
 
for /r %PROJECT_ROOT%\obj\local %%i in (*.a) do (
	for %%j in ("%%~dpi.") do (
		mkdir %OUTPUT_DIR%\%%~nj
		move %%i %OUTPUT_DIR%\%%~nj
	)
)
::copy %%i %OUTPUT_DIR%\%%~nj\%%~nxi

rd /s/q %PROJECT_ROOT%\obj

copy %PROJECT_ROOT%\libAndroid.mk %OUTPUT_DIR%\Android.mk

goto :EOF