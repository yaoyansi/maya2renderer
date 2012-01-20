- Development environment
   - msvc 2008(sp1)
   - Boost(1.46.1 or later), set BOOST_ROOT in system environment variables, e.g. BOOST_ROOT=E:/dev/boost/1_46_1
   - Maya2009 x32, set MAYA_PATH2009 in system environment variables, e.g. MAYA_PATH2009=D:\Program Files\Autodesk\Maya2009
   - (For renderman renderer only) Renderman(http://code.google.com/p/hojocn/downloads/detail?name=pixar_win32.7z&can=2&q=#makechanges)

- Build
  - access https://github.com/yaoyansi/maya2renderer, check out the code to your local directory, say it $(LiquidRoot).
    The directory structure should be：
       $(LiquidRoot)\
                 +---2.3.3\
                 +---dependence\
	         ...
  - check out Elvishray http://elvishrender.googlecode.com/svn/trunk (r1014 for now) to $(LiquidRoot)/dependence/elvishray/trunk/
    The directory structure should be:
       $(LiquidRoot)\
                 +---2.3.3\
                 +---dependence/elvishray/trunk/
                                            +-- eiAPI/
                                            +-- eiCOMMON/
                                            +-- eiCORE/
                                            ...
  - open $(LiquidRoot)\2.3.3\src\MSVC2005\liquid.sln, choose “Win32” and “Prman2009Debug” in Configuration Manager，
    - (For renderman renderer only)
      - build displayDriverAqsis project, liqmaya.dll will be generated;
      - make sure liqmaya.dll is copied to "$(RMANTREE)\etc\d_liqmaya.dll"。
    - build liquid project；

- Install
  - backup your original (My_Documents_DIR)\maya\2009\Maya.env
  - copy $(LiquidRoot)\2.3.3\bin\Maya.env to (My_Documents_DIR)\maya\2009\Maya.env
  - open (My_Documents_DIR)\maya\2009\Maya.env, set LIQUID_ROOT to your liquid directory $(LiquidRoot),
     e.g.  LIQUID_ROOT = E:/dev/autodesk/maya/myplugin/project/liquid_
  - (For Elvishray renderer only)
    you must copy manager.ini of Elvishray to $(MAYA_PATH2009)/bin/
     - copy $(LiquidRoot)\dependence\elvishray\trunk\build\r1008\x86_Debug\manager.ini to $(MAYA_PATH2009)/bin/
     - open $(MAYA_PATH2009)/bin/manager.ini, set searchpath to the directory which contain eiIMG.dll and eiSHADER.dll
	e.g. if $(MAYA_PATH2009)/bin/manager.ini doesn't has searchpath, you can append the follow line to manager.ini
	searchpath E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/elvishray/trunk/build/r1008/x86_Debug

- Test 
  - open maya2009, load $(LiquidRoot)\2.3.3\test\er.ma,
  - in "Render Settings" panel
    - select Liquid renderer
    - in liquid tab：
       - set "Debug-->NewTranslator(refactoring)" checked.
       - set "Renderer-->Renderer" to elvishray
  - render.


- link error boost::system::get_system_category() 找不到
  解决方法：在liquid项目里把\boost\1_39\libs\system\src\error_code.cpp包含进去


- liquid生成的rib文件，用renderman studio it.exe 测试
  对于liquid生成的rib脚本,把Display里的"liqmaya"改成"it"
  例如$(LiquidRoot)\2.3.3\test\render_with_rms_it\_perspShape.0010.rib里的“liqmaya”已经改为"it"。
  - 由于liquid生成的rib使用绝对路径，所以将$(LiquidRoot)\2.3.3\test\render_with_rms_it\*.*拷贝到E:\MyDocuments\maya\projects\default\rib，
  - 必须先打开it。（D:\Program Files\Pixar\RenderMan-Studio-1.0.1-Maya2008\bin\it.exe）
  - 运行test.bat


-deepShadow测试
 - 打开$(LiquidRoot)\2.3.3\test\test_deepshadow\test_deepshadow.ma
 - 菜单Liquid-》Helpers-》Convert Shading Network To RSL
 - RenderSettings面板
   - 选择Liquid渲染器
   - liquid面板里：勾选NewTranslator(refactoring)；Renderer里选择renderman；
 - 渲染


- compile $(LiquidRoot)\2.3.3\lib\shaders\*.sl
  - You must set RMS_ROOT to you RendermanStudio install directory(e.g.D:\Program Files\Pixar\RenderMan-Studio-1.0.1-Maya2008) in system enviroment variables.
  - run $(LiquidRoot)\2.3.3\lib\shaders\compile.cmd


- MakeTextute 测试
  - 把$(LiquidRoot)\2.3.3\test\test_rm_texture\textures\*.* 拷贝到E:\MyDocuments\maya\projects\default\rmantex下，再运行test case
  - 可行的texture路径格式
      E:/MyDocuments/maya/projects/default/rmantex/check10.tex
      E:/MyDocuments/maya/projects/default/rmantex/check11.bmp (Note: have to set "Map&Texture" to "rmantex")
      E:/MyDocuments/maya/projects/default/rmantex/a.b/check.14.bmp (Note: have to set "Map&Texture" to "rmantex/a.b")
  - 不可行的texture路径格式
      E:\MyDocuments\maya\projects\default\rmantex/check10.tex(反斜杠‘\’)
  - 测试用例 $(LiquidRoot)\2.3.3\test\test_rm_texture\*.*


- er渲染不出mesh，脚本里有mesh数据，但mesh的material名称为空，例如：
    ei_instance("pCubeShape3");
       ei_add_material("");
       ei_element("pCubeShape3_object");
       ei_motion(1);
    ei_end_instance();
  解决方法，选择该mesh，点击菜单Liquid-》Helpers-》Convert Shading Network To RSL。


- export shader graph with new code(C++)
  - select "Render Settings-->Liquid-->Frame-->Debug-->OutputShaderGraph(ER)"
    Note: This option will output the shader graph but not render the scene.
    So, if you render with renderman, it will complain:
        "Error: liquidNewShaderNode : shader is not readable >
         E:/MyDocuments/maya/projects/default/generatedShader/<YourShaderName>.slo //"
    Just ingore this error, it will disappear after you uncheck the "OutputShaderGraph(ER)" option.
  - set "Render Settings-->Liquid-->File-->Directories-->GeneratedShaders" to "generatedShader"
  - edit the shader or shader graph
  - assign the shader to a mesh
  - select the mesh
  - render. The shader will be generated at ,e.g. E:/MyDocuments/maya/projects/default/generatedShader/<YourShaderName>.er
  - test case: $(LiquidRoot)\2.3.3\test\test_shader_graph\er_rm_shader_graph.ma

- liquidDisplacement测试
  - test case: 2.3.3\test\test_rm_displacement\test_displacement.ma
  - 渲染时，如果liquidDisplacement1的效果出不来，
    需要在liquidDisplacement1的标签页里点击“Reload”按钮。
    这时“liquidDisplacement1-->RIB”标签页的参数就可以显示出来了
    再点击渲染，就可以了。
  - 未被选中的mesh的*.erapi,*.rmsg,*.sl_my是无法输出的

- ei_material(), shading group测试
  - test case:2.3.3\test\test_shadinggroup\er_rm_shadinggroup.ma
  - ei_material相当于maya里的shading group，
    surface shader，volume shader，displament shader仍使用maya里的数据，
    liqShadowShader，liqEnvironmentShader，liqPhotonShader供er使用，
    在mesh shape对应的shadinggroup标签的“ExtraAttributes”里有liqShadowShader，liqEnvironmentShader，liqPhotonShader


- er batch render
  - test case: maya_render_er.bat, 2.3.3\test\test_er_shader\er_shader_lambert.ma







