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

set GX_TE=%GX_ROOT%\bin\gx_te.exe

set SRC_ROOT=%LIBRARY_ROOT%\src

set INCLUDE_DIR=%LIBRARY_ROOT%\include\
if not exist %INCLUDE_DIR% (
	mkdir %INCLUDE_DIR%
)
set OUTPUT_H_DIR=%INCLUDE_DIR%\win\
if exist %OUTPUT_H_DIR% (
	rd /s/q %OUTPUT_H_DIR%
)
mkdir %OUTPUT_H_DIR%

call %GX_ROOT%\bin\cmake_.bat
call %GX_ROOT%\bin\vc.bat



:BUILD_X86
mkdir %PROJECT_ROOT%\build
pushd %PROJECT_ROOT%\build
cmake -G"Visual Studio 14 2015" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_CXX_FLAGS="-DXML_UNICODE" %SRC_ROOT%
%GX_TE% -i expat.vcxproj -o expat.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild expat.vcxproj /t:Rebuild /p:Configuration=Debug,OutDir=..\..\..\lib\win\vc\x86\Debug\
msbuild expat.vcxproj /t:Rebuild /p:Configuration=Release,OutDir=..\..\..\lib\win\vc\x86\Release\
copy /y expat_config.h %OUTPUT_H_DIR%
popd
rd /s/q %PROJECT_ROOT%\build

:BUILD_X64
mkdir %PROJECT_ROOT%\build
pushd %PROJECT_ROOT%\build
cmake -G"Visual Studio 14 2015 Win64" -DBUILD_examples=FALSE -DBUILD_shared=FALSE -DBUILD_tests=FALSE -DBUILD_tools=FALSE -DCMAKE_CXX_FLAGS="-DXML_UNICODE" %SRC_ROOT%
%GX_TE% -i expat.vcxproj -o expat.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild expat.vcxproj /t:Rebuild /p:Configuration=Debug,OutDir=..\..\..\lib\win\vc\x64\Debug\
msbuild expat.vcxproj /t:Rebuild /p:Configuration=Release,OutDir=..\..\..\lib\win\vc\x64\Release\
copy /y expat_config.h %OUTPUT_H_DIR%
popd
rd /s/q %PROJECT_ROOT%\build

copy /y %SRC_ROOT%\lib\expat.h %INCLUDE_DIR%
copy /y %SRC_ROOT%\lib\expat_external.h %INCLUDE_DIR%

goto :EOF