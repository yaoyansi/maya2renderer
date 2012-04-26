@echo off

rem set RMS_ROOT="D:\Program Files\Pixar\RenderMan-Studio-1.0.1-Maya2008"
echo "you MUST set RMS_ROOT in OS environment variables, or there maybe compile errors."
echo "and the directory can not contain '.' at all."

rem PRMan
for %%i in (*.sl) do shader -I"%RMS_ROOT%\lib\shaders\src" %%i

del *.i

pause
