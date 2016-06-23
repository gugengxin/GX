@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

call %GX_ROOT%\tool\cmd\build\build_all.bat

call %GX_ROOT%\external\freetype\project\vs\build.bat
call %GX_ROOT%\external\freetype\project\android\build.bat

call %GX_ROOT%\external\libjpeg\project\vs\build.bat
call %GX_ROOT%\external\libjpeg\project\android\build.bat

call %GX_ROOT%\external\libpng\project\vs\build.bat
call %GX_ROOT%\external\libpng\project\android\build.bat

call %GX_ROOT%\external\openal\project\vs\build.bat
call %GX_ROOT%\external\openal\project\android\build.bat

call %GX_ROOT%\external\pthread-win32\project\vs\build.bat

call %GX_ROOT%\external\zlib\project\vs\build.bat
call %GX_ROOT%\external\zlib\project\android\build.bat

pause
