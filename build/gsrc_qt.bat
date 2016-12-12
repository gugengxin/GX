@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe

%GX_TE% -i %GX_ROOT%\project\qt\GX.pro -o %GX_ROOT%\project\qt\GX.pro -fp "#__SOURCES_START__" -fs "#__SOURCES_END__" -fd %GX_ROOT%/src -fe .cpp -fe .c -fsp "\t../../src" -fss "\\n" -ff GBuffer.cpp -ff GD3DContext.cpp -ff GDShader.cpp -ff GJNI.cpp -ff GAndroid.cpp -ff GAndroidC.cpp -ff GAndroidJ.cpp -ff glew.c -ff GXCWnd.cpp -ff GXDirectX.cpp -ff GMShader.cpp -ff GMTLContext.cpp -ff GXMetal.cpp -ff GMShader.cpp -fsfp "\t#../../src" -fsfs "\\n" -fi GXPthread.cpp

%GX_TE% -i %GX_ROOT%/project/qt/GX.pro -o %GX_ROOT%/project/qt/GX.pro -fp "#__HEADERS_START__" -fs "#__HEADERS_END__" -fd %GX_ROOT%/src -fe .h -fsp "\t../../src" -fss "\\n"

pause