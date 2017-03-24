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
set BUILD_ROOT=%PROJECT_ROOT%\build

call %GX_ROOT%\bin\cmake.bat
call %GX_ROOT%\bin\vc.bat

if exist %BUILD_ROOT% (
	rd /s/q %BUILD_ROOT%
)
mkdir %BUILD_ROOT%
pushd %BUILD_ROOT%
cmake.exe -G"Visual Studio 14 2015" -DLIBTYPE=STATIC -DALSOFT_EXAMPLES=FALSE -DALSOFT_INSTALL=FALSE -DALSOFT_TEST=FALSE -DALSOFT_UTILS=FALSE %SRC_ROOT%
%GX_TE% -i OpenAL32.vcxproj -o OpenAL32.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
%GX_TE% -i common.vcxproj -o common.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Debug,Platform=Win32,OutDir=..\..\..\lib\win\vc\x86\Debug\
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Release,Platform=Win32,OutDir=..\..\..\lib\win\vc\x86\Release\
popd
rd /s/q %BUILD_ROOT%
mkdir %BUILD_ROOT%

pushd %BUILD_ROOT%
cmake.exe -G"Visual Studio 14 2015 Win64" -DLIBTYPE=STATIC -DALSOFT_EXAMPLES=FALSE -DALSOFT_INSTALL=FALSE -DALSOFT_TEST=FALSE -DALSOFT_UTILS=FALSE %SRC_ROOT%
%GX_TE% -i OpenAL32.vcxproj -o OpenAL32.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
%GX_TE% -i common.vcxproj -o common.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Debug,Platform=x64,OutDir=..\..\..\lib\win\vc\x64\Debug\
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Release,Platform=x64,OutDir=..\..\..\lib\win\vc\x64\Release\
popd
rd /s/q %BUILD_ROOT%

goto :EOF