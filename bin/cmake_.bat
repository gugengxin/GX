@echo off

echo Setup CMake(V3.7 or higher) environment

call :CMD_EXIST cmake.exe || ( 
	set /p GX_CMAKE_ROOT=Please input CMake path: 
)
set PATH=%GX_CMAKE_ROOT%\bin;%PATH%

goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0