@echo off
pushd %~dp0\..
set GX_ROOT=%cd%
popd

set GX_BIN=%GX_ROOT%\bin
set GX_TE=%GX_BIN%\gx_te.exe


for /r %GX_ROOT%\core\src %%i in (*.h,*.cpp,*.c) do (
	echo %%i
	%GX_TE% -i %%i -o %%i -oe UTF-8 -oebom8 1
)

for /r %GX_ROOT%\core\test\src %%i in (*.h,*.cpp,*.c) do (
	echo %%i
	%GX_TE% -i %%i -o %%i -oe UTF-8 -oebom8 1
)

for /r %GX_ROOT%\tool\cmd\shared_src %%i in (*.h,*.cpp,*.c) do (
	echo %%i
	%GX_TE% -i %%i -o %%i -oe UTF-8 -oebom8 1
)

pause
