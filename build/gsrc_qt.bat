@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe

::core
set PRO_FILE=%GX_ROOT%\core\project\qt\GXCore.pro
%GX_TE% -i %PRO_FILE% -o %PRO_FILE% -fp "#__SOURCES_START__" -fs "#__SOURCES_END__" -fd %GX_ROOT%\core\src -fe .cpp -fe .c -fsp "\t../../src" -fss "\\n" -ff GJNI.cpp -ff GAndroidApp.cpp -ff GXCWnd.cpp -fsfp "\t#../../src" -fsfs "\\n" -fi GXPthread.cpp

%GX_TE% -i %PRO_FILE% -o %PRO_FILE% -fp "#__HEADERS_START__" -fs "#__HEADERS_END__" -fd %GX_ROOT%\core\src -fe .h -fsp "\t../../src" -fss "\\n"

::game
set PRO_FILE=%GX_ROOT%\game\project\qt\GXGame.pro
%GX_TE% -i %PRO_FILE% -o %PRO_FILE% -fp "#__SOURCES_START__" -fs "#__SOURCES_END__" -fd %GX_ROOT%\game\src -fe .cpp -fe .c -fsp "\t../../src" -fss "\\n" -ff GAndroidEntrance.cpp -ff GAndroidActivity.cpp -ff GAndroidDaydream.cpp -ff GBuffer.cpp -ff GD3DContext.cpp -ff GDShader.cpp -ff GMShader.cpp -ff GMTLContext.cpp -ff GXDirectX.cpp -ff GXMetal.cpp -ff glew.c -fsfp "\t#../../src" -fsfs "\\n"

%GX_TE% -i %PRO_FILE% -o %PRO_FILE% -fp "#__HEADERS_START__" -fs "#__HEADERS_END__" -fd %GX_ROOT%\game\src -fe .h -fsp "\t../../src" -fss "\\n"

pause