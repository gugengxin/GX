@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_SL=%GX_BIN%\gx_sl.exe


%GX_SL% -i %GX_ROOT%\game\src\GSRGraphics.cpp -o %GX_ROOT%\game\src\GSRGraphics.gxsl
%GX_SL% -i %GX_ROOT%\game\src\GSRTexture2D.cpp -o %GX_ROOT%\game\src\GSRTexture2D.gxsl

pause