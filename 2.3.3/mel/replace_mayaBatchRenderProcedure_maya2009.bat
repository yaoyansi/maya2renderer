echo off
set MAYA_ROOT=D:\Program Files\Autodesk\Maya2009


if not exist %MAYA_ROOT%\scripts\others\mayaBatchRenderProcedure_bak.mel ( 
echo ---------backup mayaBatchRenderProcedure.mel--------------"
ren "%MAYA_ROOT%\scripts\others\mayaBatchRenderProcedure.mel" mayaBatchRenderProcedure_bak.mel
)

echo "--------replace mayaBatchRenderProcedure.mel--------------"
copy .\xxliquidmayaBatchRenderProcedure_maya2009.mel "%MAYA_ROOT%\scripts\others\mayaBatchRenderProcedure.mel"

pause