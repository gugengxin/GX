@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe


for /r %GX_ROOT%\src %%i in (*.h,*.cpp) do (
	echo %%i
	%GX_TE% -i %%i -o %%i -oe UTF-8 -oebom8 1
)

pause
