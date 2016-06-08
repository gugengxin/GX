@echo off

echo Setup VC120 environment

call :CMD_EXIST msbuild || ( 
	call %~dp0vc12_amd64_vcvars64.bat
)

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0