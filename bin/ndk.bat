@echo off

echo Setup NDK environment

call :CMD_EXIST ndk-build.cmd || ( 
	set /p GX_NDK_ROOT=Please input NDK path: 
)
set PATH=%GX_NDK_ROOT%;%PATH%

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0