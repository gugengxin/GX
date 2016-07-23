@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe

%GX_TE% -i %GX_ROOT%\project\as\gx\src\main\cpp\Android.mk -o %GX_ROOT%\project\as\gx\src\main\cpp\Android.mk -fp "#__LOCAL_SRC_FILES_START__" -fs "#__LOCAL_SRC_FILES_END__" -fd %GX_ROOT%/src -fe .cpp -fe .c -fsp "LOCAL_SRC_FILES += $(ENGINE_PATH_FROM_SRC)/src" -fss "\n"

pause