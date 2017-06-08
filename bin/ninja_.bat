@echo off

echo Setup Ninja environment

call :CMD_EXIST ninja.exe || goto :CMD_NO
goto :CMD_YES

:CMD_NO
set /p GX_NINJA_ROOT=Please input Ninja path: 
echo PATH add %GX_NINJA_ROOT%
set "PATH=%GX_NINJA_ROOT%;%PATH%"

:CMD_YES

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%
:: ;%~dp0;%cd% no need these
if "%~$PATH:1"=="" exit /b 1
exit /b 0