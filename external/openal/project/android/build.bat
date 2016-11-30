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

set SRC_ROOT=%LIBRARY_ROOT%\src

if exist %SRC_ROOT%\android (
	rd /s/q %SRC_ROOT%\android
)
mkdir %SRC_ROOT%\android\jni
copy /y %PROJECT_ROOT%\jni\* %SRC_ROOT%\android\jni

set OUTPUT_DIR=%LIBRARY_ROOT%\lib\ard
if exist %OUTPUT_DIR% (
	rd /s/q %OUTPUT_DIR%
)
mkdir %OUTPUT_DIR%

set OUTPUT_INC=%LIBRARY_ROOT%\include
if exist %OUTPUT_INC% (
	rd /s/q %OUTPUT_INC%
)

call %GX_ROOT%\bin\ndk.bat

call ndk-build.cmd NDK_PROJECT_PATH=%SRC_ROOT%\android

xcopy /y /e /i %SRC_ROOT%\include %OUTPUT_INC%
for /r %SRC_ROOT%\android\obj\local %%i in (*.a) do (
	for %%j in ("%%~dpi.") do (
		mkdir %OUTPUT_DIR%\%%~nj
		move %%i %OUTPUT_DIR%\%%~nj
	)
)

rd /s/q %SRC_ROOT%\android

copy /y %PROJECT_ROOT%\libAndroid.mk %OUTPUT_DIR%\Android.mk

goto :EOF