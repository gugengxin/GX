@echo off

echo Setup VC environment

call :CMD_EXIST msbuild || ( 
	call %~dp0vcvars64.bat
)

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0