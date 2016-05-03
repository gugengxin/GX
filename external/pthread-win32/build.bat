@echo off

pushd %~dp0\..\..
set GX_ROOT=%cd%
popd
pushd %~dp0
set PROJECT_ROOT=%cd%
popd

set MY_UNZIP=%GX_ROOT%\bin\unzip.exe

if exist "%PROJECT_ROOT%\pthread-win32" (
	rd /s /q %PROJECT_ROOT%\pthread-win32
)
if not exist "%PROJECT_ROOT%\include" (
	md %PROJECT_ROOT%\include
)

%MY_UNZIP% %PROJECT_ROOT%\pthread-win32.zip -d %PROJECT_ROOT%
call %GX_ROOT%\bin\vc12_amd64_vcvars64.bat

pushd %PROJECT_ROOT%\pthread-win32
msbuild pthread.2013.vcxproj /t:Rebuild /p:Configuration=Debug,Platform=Win32,OutDir=..\lib\win\vc120\x86\Debug\
msbuild pthread.2013.vcxproj /t:Rebuild /p:Configuration=Release,Platform=Win32,OutDir=..\lib\win\vc120\x86\Release\
msbuild pthread.2013.vcxproj /t:Rebuild /p:Configuration=Debug,Platform=x64,OutDir=..\lib\win\vc120\x64\Debug\
msbuild pthread.2013.vcxproj /t:Rebuild /p:Configuration=Release,Platform=x64,OutDir=..\lib\win\vc120\x64\Release\
copy /y .\pthread.h %PROJECT_ROOT%\include
copy /y .\sched.h %PROJECT_ROOT%\include
popd

if exist "%PROJECT_ROOT%\pthread-win32" (
	rd /s /q %PROJECT_ROOT%\pthread-win32
)
      
