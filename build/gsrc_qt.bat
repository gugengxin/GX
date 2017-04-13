@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe

::core
%GX_TE% -i %GX_ROOT%\core\project\qt\GXCore.pro -o %GX_ROOT%\core\project\qt\GXCore.pro -fp "#__SOURCES_START__" -fs "#__SOURCES_END__" -fd %GX_ROOT%/core/src -fe .cpp -fe .c -fsp "\t../../src" -fss "\\\n" -ff GJNI.cpp -ff GAndroidApp.cpp -ff glew.c -ff GXCWnd.cpp -fsfp "\t#../../src" -fsfs "\\\n" -fi GXPthread.cpp

%GX_TE% -i %GX_ROOT%\core\project\qt\GXCore.pro -o %GX_ROOT%\core\project\qt\GXCore.pro  -fp "#__HEADERS_START__" -fs "#__HEADERS_END__" -fd %GX_ROOT%\core\src -fe .h -fsp "\t../../src" -fss "\\\n"

pause