echo off
echo ---------------------------NOTE------------------------------------------
echo 1.make sure ConvertParameters(),Subdivide(),Free() are exported.
echo 2.make sure dso can be found in PATH.
echo 3.make sure "it" is launched.
echo -------------------------------------------------------------------------
echo >>start ....

prman -rif E:/dev/autodesk/maya/myplugin/project/liquid_/2.3.3/lib/plugins/pointToDSO.dll E:/MyDocuments/maya/projects/default/rib/_perspShape.0011.rib

echo >>end.
pause