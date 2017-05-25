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

call %GX_ROOT%\bin\cmake_.bat
call %GX_ROOT%\bin\ninja.bat
call %GX_ROOT%\bin\ndk.bat


set OUTPUT_DIR=%LIBRARY_ROOT%\lib\ard
if exist %OUTPUT_DIR% (
	rd /s/q %OUTPUT_DIR%
)
mkdir %OUTPUT_DIR%

set TARGET_NAME=harfbuzz

if exist "%PROJECT_ROOT%\build" (
	rd /s/q %PROJECT_ROOT%\build
)
mkdir %PROJECT_ROOT%\build
pushd %PROJECT_ROOT%\build

for %%i in ( "armeabi","armeabi-v7a","arm64-v8a","x86","x86_64","mips","mips64" ) do (
	
	setlocal EnableDelayedExpansion
	
	set ARCH_ABI=%%i
	
	if !ARCH_ABI!=="arm64-v8a" (
		set API_LEVEL=21
	) else if !ARCH_ABI!=="x86_64" (
		set API_LEVEL=21
	) else if !ARCH_ABI!=="mips64" (
		set API_LEVEL=21
	) else (
		set API_LEVEL=14
	)
	
	mkdir !ARCH_ABI!
	pushd !ARCH_ABI!
	cmake -GNinja -D"CMAKE_TOOLCHAIN_FILE=%GX_ROOT%\bin\android.toolchain.cmake" -D"CMAKE_ANDROID_NDK=%ANDROID_NDK_ROOT_FOR_CMAKE%" -D"CMAKE_ANDROID_ARCH_ABI=!ARCH_ABI!" -D"CMAKE_SYSTEM_VERSION=!API_LEVEL!" -D"HB_HAVE_FREETYPE=FALSE" -D"HB_HAVE_GLIB=FALSE" %SRC_ROOT%
	ninja -C .
	mkdir %OUTPUT_DIR%\!ARCH_ABI!
	move lib%TARGET_NAME%.a %OUTPUT_DIR%\!ARCH_ABI!\%TARGET_NAME%.a
	popd
	
	endlocal
)

popd

copy /y %PROJECT_ROOT%\libAndroid.mk %OUTPUT_DIR%\Android.mk

rd /s/q %PROJECT_ROOT%\build

set INCLUDE_DIR=%LIBRARY_ROOT%\include

if exist %INCLUDE_DIR% (
	rd /s/q %INCLUDE_DIR%
)
mkdir %INCLUDE_DIR%

copy /y %SRC_ROOT%\src\*.h %INCLUDE_DIR%
copy /y %SRC_ROOT%\src\*.hh %INCLUDE_DIR%

goto :EOF