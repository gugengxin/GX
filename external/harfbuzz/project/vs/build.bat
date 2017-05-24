@echo off

pushd %~dp0
set PROJECT_ROOT=%cd%
popd
pushd %PROJECT_ROOT%\..\..
set LIBRARY_ROOT=%cd%
popd
pushd %LIBRARY_ROOT%\..\..
set GX_ROOT=%cd%
popd

set SRC_ROOT=%LIBRARY_ROOT%\src

call %GX_ROOT%\bin\cmake_.bat
call %GX_ROOT%\bin\vc.bat

mkdir %PROJECT_ROOT%\build
pushd %PROJECT_ROOT%\build
cmake -G"Visual Studio 14 2015" %SRC_ROOT%
msbuild harfbuzz.vcxproj /t:Rebuild /p:Configuration=Debug,OutDir=..\..\..\lib\win\vc\x86\Debug\
msbuild harfbuzz.vcxproj /t:Rebuild /p:Configuration=Release,OutDir=..\..\..\lib\win\vc\x86\Release\
popd
rd /s/q %PROJECT_ROOT%\build

mkdir %PROJECT_ROOT%\build
pushd %PROJECT_ROOT%\build
cmake -G"Visual Studio 14 2015 Win64" %SRC_ROOT%
msbuild harfbuzz.vcxproj /t:Rebuild /p:Configuration=Debug,OutDir=..\..\..\lib\win\vc\x64\Debug\
msbuild harfbuzz.vcxproj /t:Rebuild /p:Configuration=Release,OutDir=..\..\..\lib\win\vc\x64\Release\
popd
rd /s/q %PROJECT_ROOT%\build

set INCLUDE_DIR=%LIBRARY_ROOT%\include

if exist %INCLUDE_DIR% (
	rd /s/q %INCLUDE_DIR%
)
mkdir %INCLUDE_DIR%

copy /y %SRC_ROOT%\src\*.h %INCLUDE_DIR%


goto :EOF