@echo off

echo Setup NDK environment

call :CMD_EXIST ndk-build.cmd || ( 
	set /p GX_NDK_ROOT=Please input NDK path: 
)
set PATH=%GX_NDK_ROOT%;%PATH%

if "%ANDROID_NDK_ROOT%"=="" for /f "delims=" %%t in ('where ndk-build') do set ANDROID_NDK_ROOT=%%~dpt
set ANDROID_NDK_ROOT_FOR_CMAKE=%ANDROID_NDK_ROOT:\=/%

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0