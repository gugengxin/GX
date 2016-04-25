@echo off

call :CMD_EXIST qtenv2.bat || (
	set /p GX_QT_SDK="Please input QT SDK path: "
)
pushd .
if "%GX_QT_SDK%"=="" (
	call qtenv2.bat
) else (
	call %GX_QT_SDK%\bin\qtenv2.bat
)
popd

set GX_QMAKE=qmake.exe

pushd %~dp0
cd ..\..\..
set GX_ROOT=%cd%
popd
set GX_BIN=%GX_ROOT%\bin
call %GX_BIN%\vc12_amd64_vcvars64.bat

::text editor
set ROOT_DIR=%GX_ROOT%\tool\cmd\text_editor
set PROJECT_DIR=%ROOT_DIR%\project\qt
set BUILD_DIR=%PROJECT_DIR%\build

if EXIST %BUILD_DIR% (
	rd /s /q %BUILD_DIR%
)
mkdir %BUILD_DIR%
pushd %BUILD_DIR%
%GX_QMAKE% -makefile %PROJECT_DIR%\gx_te.pro
nmake
copy .\release\gx_te.exe %GX_BIN%
popd
rd /s /q %BUILD_DIR%

windeployqt.exe --no-translations %GX_BIN%\gx_te.exe


goto :EOF

:CMD_EXIST
setlocal&PATH %PATH%;%~dp0;%cd%
if "%~$PATH:1"=="" exit /b 1
exit /b 0
