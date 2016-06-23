@echo off

pushd %~dp0
cd ..\..\..
set GX_ROOT=%cd%
popd
set GX_BIN=%GX_ROOT%\bin
call %GX_BIN%\qt.bat
call %GX_BIN%\vc120.bat

set QT_QMAKE=qmake.exe
set QT_DEPLOY=windeployqt.exe

SET PROJECTS_LEN=0

SET PROJECTS[%PROJECTS_LEN%].dirName=text_editor
SET PROJECTS[%PROJECTS_LEN%].projectName=gx_te
SET /A PROJECTS_LEN=%PROJECTS_LEN%+1

SET PROJECTS[%PROJECTS_LEN%].dirName=sl
SET PROJECTS[%PROJECTS_LEN%].projectName=gx_sl
SET /A PROJECTS_LEN=%PROJECTS_LEN%+1

SET Obj_Index=0  
:LoopStart
	IF %Obj_Index% EQU %PROJECTS_LEN% GOTO :LoopNext

	SET Obj_Current.dirName=0
	SET Obj_Current.projectName=0
	
	FOR /F "usebackq delims==. tokens=1-3" %%I IN (`SET PROJECTS[%Obj_Index%]`) DO (
		SET Obj_Current.%%J=%%K
	)
	
	set ROOT_DIR=%GX_ROOT%\tool\cmd\%Obj_Current.dirName%
	set PROJECT_DIR=%ROOT_DIR%\project\qt
	set BUILD_DIR=%PROJECT_DIR%\build

	if EXIST %BUILD_DIR% (
		rd /s /q %BUILD_DIR%
	)
	mkdir %BUILD_DIR%
	pushd %BUILD_DIR%
	%QT_QMAKE% -makefile %PROJECT_DIR%\%Obj_Current.projectName%.pro
	nmake
	copy .\release\%Obj_Current.projectName%.exe %GX_BIN%
	popd
	rd /s /q %BUILD_DIR%

	%QT_DEPLOY% --no-translations %GX_BIN%\%Obj_Current.projectName%.exe
  
	SET /A Obj_Index=%Obj_Index% + 1
GOTO LoopStart
:LoopNext
