@echo off

echo Setup Qt environment

call :CMD_EXIST qmake.exe || goto :CMD_NO
goto :CMD_YES

:CMD_NO
set /p GX_QT_ROOT=Please input Qt path: 
echo PATH add %GX_QT_ROOT%
set PATH=%GX_QT_ROOT%\bin;%PATH%

:CMD_YES

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%
:: ;%~dp0;%cd% no need these
if "%~$PATH:1"=="" exit /b 1
exit /b 0