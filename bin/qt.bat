@echo off

echo Setup Qt environment

call :CMD_EXIST qmake.exe || ( 
	set /p GX_QT_ROOT=Please input Qt path: 
)
set PATH=%GX_QT_ROOT%\bin;%PATH%

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0