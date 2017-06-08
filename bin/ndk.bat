@echo off

echo Setup NDK environment

call :CMD_EXIST ndk-build.cmd || goto :CMD_NO
goto :CMD_YES

:CMD_NO
set /p GX_NDK_ROOT=Please input NDK path: 
echo PATH add %GX_NDK_ROOT%
set PATH=%GX_NDK_ROOT%;%PATH%

:CMD_YES
if "%ANDROID_NDK_ROOT%"=="" for /f "delims=" %%t in ('where ndk-build') do set ANDROID_NDK_ROOT=%%~dpt
set ANDROID_NDK_ROOT_FOR_CMAKE=%ANDROID_NDK_ROOT:\=/%

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%
:: ;%~dp0;%cd% no need these
if "%~$PATH:1"=="" exit /b 1
exit /b 0