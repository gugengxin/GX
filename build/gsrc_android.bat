@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe

::core
set MK_FILE=%GX_ROOT%\core\project\as\gxcore\src\main\cpp\Android.mk
%GX_TE% -i %MK_FILE% -o %MK_FILE% -fp "#__LOCAL_SRC_FILES_START__" -fs "#__LOCAL_SRC_FILES_END__" -fd %GX_ROOT%\core\src -fe .cpp -fe .c -fsp "LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/core/src" -fss "\n" -fi GJNI.cpp -fi GAndroidApp.cpp

::game
set MK_FILE=%GX_ROOT%\game\project\as\gxgame\src\main\cpp\Android.mk
%GX_TE% -i %MK_FILE% -o %MK_FILE% -fp "#__LOCAL_SRC_FILES_START__" -fs "#__LOCAL_SRC_FILES_END__" -fd %GX_ROOT%\game\src -fe .cpp -fe .c -fsp "LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/game/src" -fss "\n" -fi GAndroidEntrance.cpp -fi GAndroidActivity.cpp -fi GAndroidDaydream.cpp

pause