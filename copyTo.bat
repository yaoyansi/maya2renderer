rem ---------------------------zip-----------------------------------------------
set ZIP="D:\Program Files\7-Zip\7z.exe"

rem ---------------------------soruce-----------------------------------------------
set MYPLUGIN_ROOT=E:\dev\autodesk\maya\myplugin\project
set COMMON_ROOT=%MYPLUGIN_ROOT%\common
set PROJ_NAME=liquid_
set THIS_ROOT=%MYPLUGIN_ROOT%\%PROJ_NAME%


rem ---------------------------destination------------------------------------------
set DESTINITY_ROOT=E:\Tmp
set DESTINITY_CODE_ROOT=%DESTINITY_ROOT%\root
set DESTINITY_PLUGIN_ROOT=%DESTINITY_CODE_ROOT%\myplugin\project


rem ---------------------------xcopy------------------------------------------------
xcopy /s /d /y    %COMMON_ROOT%\*.*               %DESTINITY_PLUGIN_ROOT%\common\
xcopy /s /d /c /y /EXCLUDE:exclude.txt %THIS_ROOT%\*.*           %DESTINITY_PLUGIN_ROOT%\%PROJ_NAME%\  


%ZIP%  u  %DESTINITY_ROOT%\liquid.7z %DESTINITY_CODE_ROOT%\

del /f /s /q   %DESTINITY_CODE_ROOT%\
RD /S /Q %DESTINITY_CODE_ROOT%

pause