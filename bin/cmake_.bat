@echo off

echo Setup CMake(V3.7 or higher) environment

call :CMD_EXIST cmake.exe || goto :CMD_NO
goto :CMD_YES

:CMD_NO
set /p GX_CMAKE_ROOT=Please input CMake path: 
echo PATH add %GX_CMAKE_ROOT%
set "PATH=%GX_CMAKE_ROOT%\bin;%PATH%"

:CMD_YES

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%
:: ;%~dp0;%cd% no need these
if "%~$PATH:1"=="" exit /b 1
exit /b 0