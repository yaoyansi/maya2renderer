echo off
set MAYA_2008_ROOT=D:\Program Files\Autodesk\Maya2008


if not exist %MAYA_2008_ROOT%\scripts\others\mayaBatchRenderProcedure_bak.mel ( 
echo ---------backup mayaBatchRenderProcedure.mel--------------"
ren "%MAYA_2008_ROOT%\scripts\others\mayaBatchRenderProcedure.mel" mayaBatchRenderProcedure_bak.mel
)

echo "--------replace mayaBatchRenderProcedure.mel--------------"
copy .\xxliquidmayaBatchRenderProcedure.mel "%MAYA_2008_ROOT%\scripts\others\mayaBatchRenderProcedure.mel"

pause