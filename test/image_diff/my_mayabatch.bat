set TEST_FILE=%1%
set LiqRenderer=%2%

set MAYA_LOCATION=D:\Program Files\Autodesk\Maya2009
set PYTHONHOME=D:\Program Files\Autodesk\Maya2009\Python
set PYTHONPATH=D:\Program Files\Autodesk\Maya2009\bin\python25.zip;D:\Program Files\Autodesk\Maya2009\Python\lib\site-packages

mayabatch -file "%TEST_FILE%" -command "source \"registerLiquidRenderer.mel\"; registerLiquidRenderer(); setAttr -type \"string\" liquidGlobals.renderer %LiqRenderer%; mayaBatchRenderProcedure(0,\"\",\"\",\"liquid\",\"\");"
