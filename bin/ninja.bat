@echo off

echo Setup Ninja environment

call :CMD_EXIST ninja.exe || ( 
	set /p GX_NINJA_ROOT=Please input Ninja path: 
)
set PATH=%GX_NINJA_ROOT%\bin;%PATH%

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0