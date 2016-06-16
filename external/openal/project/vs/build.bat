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

set SRC_DIR=openal-soft-openal-soft-1.17.2
set SRC_ROOT=%PROJECT_ROOT%\%SRC_DIR%
if exist %SRC_ROOT% (
	rd /s/q %SRC_ROOT%
)
%GX_ROOT%\bin\unzip.exe %LIBRARY_ROOT%\%SRC_DIR%.zip -d %PROJECT_ROOT%

call %GX_ROOT%\bin\cmake.bat
call %GX_ROOT%\bin\vc120.bat

pushd %SRC_ROOT%\build
cmake cmake -G"Visual Studio 12 2013" -DLIBTYPE=STATIC -DALSOFT_EXAMPLES=FALSE -DALSOFT_INSTALL=FALSE -DALSOFT_TEST=FALSE -DALSOFT_UTILS=FALSE ..
%GX_TE% -i OpenAL32.vcxproj -o OpenAL32.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
%GX_TE% -i common.vcxproj -o common.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Debug,Platform=Win32,OutDir=..\..\..\..\lib\win\vc120\x86\Debug\
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Release,Platform=Win32,OutDir=..\..\..\..\lib\win\vc120\x86\Release\
popd
rd /s/q %SRC_ROOT%\build
mkdir %SRC_ROOT%\build

pushd %SRC_ROOT%\build
cmake cmake -G"Visual Studio 12 Win64" -DLIBTYPE=STATIC -DALSOFT_EXAMPLES=FALSE -DALSOFT_INSTALL=FALSE -DALSOFT_TEST=FALSE -DALSOFT_UTILS=FALSE ..
%GX_TE% -i OpenAL32.vcxproj -o OpenAL32.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
%GX_TE% -i common.vcxproj -o common.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Debug,Platform=x64,OutDir=..\..\..\..\lib\win\vc120\x64\Debug\
msbuild OpenAL32.vcxproj /t:Rebuild /p:Configuration=Release,Platform=x64,OutDir=..\..\..\..\lib\win\vc120\x64\Release\
popd

rd /s/q %SRC_ROOT%

goto :EOF