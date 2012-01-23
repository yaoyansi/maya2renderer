set LIQUID_ROOT=E:\dev\Autodesk\maya\myplugin\project\liquid_
set TEST_FILE=%LIQUID_ROOT%\2.3.3\test\test_er_shader\er_shader_lambert.ma

mayabatch -file "%TEST_FILE%" -command "source \"registerLiquidRenderer.mel\"; registerLiquidRenderer(); setAttr -type \"string\" liquidGlobals.renderer elvishray; mayaBatchRenderProcedure(0,\"\",\"\",\"liquid\",\"\");" 

mayabatch -file "%TEST_FILE%" -command "source \"registerLiquidRenderer.mel\"; registerLiquidRenderer(); setAttr -type \"string\" liquidGlobals.renderer renderman; mayaBatchRenderProcedure(0,\"\",\"\",\"liquid\",\"\");" 

pause
