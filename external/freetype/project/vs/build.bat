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

call %GX_ROOT%\bin\cmake_.bat
call %GX_ROOT%\bin\vc.bat

::Build x86
mkdir %PROJECT_ROOT%\build\x86
pushd %PROJECT_ROOT%\build\x86
cmake -G"Visual Studio 14 2015" -D"FREETYPE_NO_DIST=true" -D"WITH_ZLIB=OFF" -D"WITH_BZip2=OFF" -D"WITH_PNG=OFF" -D"WITH_HarfBuzz=OFF" %SRC_ROOT%
msbuild freetype.vcxproj /t:Rebuild /p:Configuration=Release,OutDir=..\..\..\..\lib\win\vc\x86\Release\
%GX_TE% -i freetype.vcxproj -o freetype.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild freetype.vcxproj /t:Rebuild /p:Configuration=Debug,OutDir=..\..\..\..\lib\win\vc\x86\Debug\
popd

::Build x64
mkdir %PROJECT_ROOT%\build\x64
pushd %PROJECT_ROOT%\build\x64
cmake -G"Visual Studio 14 2015 Win64" -D"FREETYPE_NO_DIST=true" -D"WITH_ZLIB=OFF" -D"WITH_BZip2=OFF" -D"WITH_PNG=OFF" -D"WITH_HarfBuzz=OFF" %SRC_ROOT%
msbuild freetype.vcxproj /t:Rebuild /p:Configuration=Release,OutDir=..\..\..\..\lib\win\vc\x64\Release\
%GX_TE% -i freetype.vcxproj -o freetype.vcxproj -rs "<AssemblerListingLocation>Debug/</AssemblerListingLocation>" -rd "<AssemblerListingLocation>Debug/</AssemblerListingLocation><ProgramDataBaseFileName>$(OutDir)$(TargetName)_vc$(PlatformToolsetVersion).pdb</ProgramDataBaseFileName>"
msbuild freetype.vcxproj /t:Rebuild /p:Configuration=Debug,OutDir=..\..\..\..\lib\win\vc\x64\Debug\
popd

::Copy Include
set OUTPUT_H_DIR=%LIBRARY_ROOT%\include\win
if exist %OUTPUT_H_DIR% (
	rd /s/q %OUTPUT_H_DIR%
)
mkdir %OUTPUT_H_DIR%
xcopy /s /e %LIBRARY_ROOT%\src\include %OUTPUT_H_DIR%
copy /y %PROJECT_ROOT%\build\x64\include\freetype\config\ftconfig.h %OUTPUT_H_DIR%\freetype\config
copy /y %PROJECT_ROOT%\build\x64\include\freetype\config\ftoption.h %OUTPUT_H_DIR%\freetype\config

::Clean
rd /s/q %PROJECT_ROOT%\build

goto :EOF