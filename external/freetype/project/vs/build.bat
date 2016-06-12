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

call %GX_ROOT%\bin\vc120.bat

msbuild %PROJECT_ROOT%\freetype.sln /t:Rebuild /p:Configuration=Debug,Platform=Win32
msbuild %PROJECT_ROOT%\freetype.sln /t:Rebuild /p:Configuration=Release,Platform=Win32
msbuild %PROJECT_ROOT%\freetype.sln /t:Rebuild /p:Configuration=Debug,Platform=x64
msbuild %PROJECT_ROOT%\freetype.sln /t:Rebuild /p:Configuration=Release,Platform=x64

goto :EOF