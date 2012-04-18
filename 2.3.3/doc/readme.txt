 ---------------------------------------------------------------------
                          CONTENTS
 ---------------------------------------------------------------------
- License
- Build/Install/Test
- Others
- NOTES
- F.A.Q.


 ---------------------------------------------------------------------
                          License
 ---------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License Version 1.1
(the "License"); you may not use this file except in compliance with the
License. You may obtain a copy of the License at http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is the Liquid Rendering Toolkit.
The Initial Developer of the Original Code is Colin Doncaster. Portions created
by Colin Doncaster are Copyright (C) 2002. All Rights Reserved.

Contributor(s): Dan Bethell, Berj Bannayan, Andrew Chapman, Colin Doncaster,
St閜hane Deverly, George Harker, Jamie McCarter, Ken McGaugh, Moritz Moeller,
Michael Duffy, Richard Pickler, Rob Pieke, Paul Scruby, Yuri Meshalkin,
Alf Kraus, Leon Tony Atkinson.

The RenderMan (R) Interface Procedures and Protocol are:
Copyright 1988, 1989, Pixar
All Rights Reserved

RenderMan (R) is a registered trademark of Pixar


 ---------------------------------------------------------------------
                          Build/Install/Test
 ---------------------------------------------------------------------
- Development environment
   - msvc 2008(sp1)
   - Boost(1.46.1 or later), set BOOST_ROOT in system environment variables, e.g. BOOST_ROOT=E:/dev/boost/1_46_1
   - Maya2009 x32, set MAYA_PATH2009 in system environment variables, e.g. MAYA_PATH2009=D:\Program Files\Autodesk\Maya2009
   - (For renderman renderer only) Renderman Pro Server.

- Build
  - access https://github.com/yaoyansi/maya2renderer, check out the code to your local directory, say it $(LiquidRoot).
    The directory structure should be：
       $(LiquidRoot)\
                 +---2.3.3\
                 +---dependence\
	         ...
  - check out Elvishray http://elvishrender.googlecode.com/svn/trunk (r1117 for now) to $(LiquidRoot)/dependence/elvishray/trunk/
    The directory structure should be:
       $(LiquidRoot)\
                 +---2.3.3\
                 +---dependence/elvishray/trunk/
                                            +-- eiAPI/
                                            +-- eiCOMMON/
                                            +-- eiCORE/
                                            ...
  - build ER. 
    - When you configure cmake for ER, set CMAKE_INSTALL_PREFIX to $(LiquidRoot)\dependence\elvishray, so ER will copy *.dll to $(LiquidRoot)\dependence\elvishray\bin\$(ConfigurationName)
    - select a ConfigurationName, e.g. Release. 
    - build ER, and copy generated *.lib to $(LiquidRoot)\dependence\elvishray\bin\$(ConfigurationName)
  - build $(LiquidRoot)\2.3.3\src\elvishray\eiSHADER_maya\build\eiSHADER_maya.sln. eiSHADER_maya.dll will be generated at $(LiquidRoot)\dependence\elvishray\bin\$(ConfigurationName)
    NOTE: you'd better set the ConfigurationName same with ER project. e.g. Release.
  - copy $(LiquidRoot)\dependence\elvishray\bin\$(ConfigurationName)\*.* to $(LiquidRoot)\dependence\elvishray\bin\$(ConfigurationName)\*.*
    e.g. you can choose Release as the ConfigurationName.
  - open $(LiquidRoot)\2.3.3\include\liqConfig.h, set _USE_SHAVE_ to 1 if shave(v61 or later) is installed, or set _USE_SHAVE_ to 0 if shave isn't installed.
  - open $(LiquidRoot)\2.3.3\src\MSVC2005\liquid.sln, choose “Win32” and “Prman2009Debug” in Configuration Manager，
    - (For renderman renderer only)
      - make sure Prman is installed, and $(RMANTREE) is set(e.g. RMANTREE=D:\Program Files\Pixar\RenderManProServer-13.5.2),
        $(RMANTREE) contains 3 sub-directories, bin\, etc\ and lib\.
      - build displayDriverAqsis project, liqmaya.dll will be generated;
      - make sure liqmaya.dll is copied to "$(RMANTREE)\etc\d_liqmaya.dll"。
    - build liquid project；

- Install
  - backup your original (My_Documents_DIR)\maya\2009\Maya.env
  - copy $(LiquidRoot)\2.3.3\bin\Maya.env to (My_Documents_DIR)\maya\2009\Maya.env
    make sure ELVISHRAY_BIN point to the ER's DLL directory which you are using.
  - open (My_Documents_DIR)\maya\2009\Maya.env, set LIQUID_ROOT to your liquid directory $(LiquidRoot),
     e.g.  LIQUID_ROOT = E:/dev/autodesk/maya/myplugin/project/liquid_
  - (For Elvishray renderer only)
    you must copy manager.ini of Elvishray to $(MAYA_PATH2009)/bin/
     - copy $(LiquidRoot)\dependence\elvishray\bin\manager.ini to $(MAYA_PATH2009)/bin/
     - open $(MAYA_PATH2009)/bin/manager.ini, set searchpath to the directory which contain eiIMG.dll and eiSHADER.dll
	e.g. if $(MAYA_PATH2009)/bin/manager.ini doesn't has searchpath, you can append the follow line to manager.ini
	searchpath E:/dev/Autodesk/maya/myplugin/project/liquid_/dependence/elvishray/bin

- Test 
  - open maya2009, load $(LiquidRoot)\2.3.3\test\er.ma,
  - load liquid plugin:
    Menu "Window" --> "Settings/Preferences" --> "Plug-in Manager"
    Liquid plugin would be listed in "Plug-in Manager" window if you use $(LiquidRoot)\2.3.3\bin\Maya.env,
    If liquid plugin is not listed, load $(LiquidRoot)\2.3.3\bin\Prman\win32\liquid_2009x32d.mll manually please.
  - in "Render Settings" panel
    - select Liquid renderer
    - in liquid tab：
       - set "Debug-->NewTranslator(refactoring)" checked.
       - set "Renderer-->Renderer" to elvishray
  - render.



 ---------------------------------------------------------------------
                            Others
 ---------------------------------------------------------------------
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


- rm ao测试（test/test_ao2/occlude2.ma），注意打开RenderSettings->Liquid->Rays->RayTracing->Enable


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


- batch render
  - er  test case: maya_render_er.bat, 2.3.3\test\test_er_shader\er_shader_lambert.ma
  - cmd batch render script: $(LiquidRoot)\2.3.3\test\mayabatch_template.bat


- liquidSurfaceShader parameters list
  - 见HowToUseLiquid.pdf的liquidSurfaceShader章节


- MotionBlur
  - 见motion_blur.pdf


- automation test
  - first, render you scene(test_motionblur\transform\deform.ma) manully, 
    and save the image as stander image to the sub-directory(output_img_std/) of your scene file, e.g. test_motionblur\transform\output_img_std/.
  - add your test scene in testall.py.test_all_scene()
        LIQUID_ROOT="E:/dev/Autodesk/maya/myplugin/project/liquid_"
        testFile=LIQUID_ROOT+"/2.3.3/test/test_motionblur/transform/deform.ma"
        liqRenderer=""
        MyTestOne.test_one_scene(testFile, liqRenderer)
    - if you set liqRenderer="elvishray", the test file will rendered with elvishray only,
      if you set liqRenderer="renderman", the test file will rendered with prman only,
      if you set liqRenderer="", the test file will rendered with both elvishray and prman.

  - run $(LiquidRoot)\test\image_diff\test.py, it will run the test and generate the log file _liqTestLog.htm



- press ESC to interrupt the rendering.


- *.pl 文件里shaderType可以使用shadow
  - use liqShader.shader_type_ex instead of liqShader.shader_type.
  - shader_type_ex can be set by shaderType-section in *.pl
  - shader_type_ex is set by liqGetSloInfo::shaderTypeEx, which comes from "$node.rmanShaderType"
  - add ".rmanShaderType" to liqSurfaceNode/liqDisplacementNode/liqCoShaderNode/liqLightNode/liqVolumeNode
  - set ".rmanShaderType" in rmanParams_create()
  - use ".rmanShaderType" in liqGetSloInfo::setShaderNode()-->shaderNode.findPlug("rmanShaderType",...);


- Depth of Field
  - RM 的DOF 只需在RenderSettings-->liquid-->Frame-->MotionBlur&DepthofField里勾选“Depth of Field”
  - ER 的DOF除了需要勾选RenderSettings-->liquid-->Frame-->MotionBlur&DepthofField里勾选“Depth of Field”，
    还需要（以test_er_dof\er_dof2.ma为例）：
    - 选中cameraShape1节点，在Depth of Field里勾选“Depth of Field”
    - Menu -->Liquid-->ObjectAttributes-->Create CustomShaderForERCamera,这样就在cameraShape1节点上建立了liqLensShader，liqEnvironmentShader属性
    - 建立DOF shader。
       - 新建liquidSurface2，将cameraShape1.liqLensShader连接到liquidSurface2上，
       - 设置liquidSurface2的参数
          - 设置shader=simple_dof.dll
	  - 连接cameraShape1.nearClipPlane到liquidSurface2.fplane
	  - 连接cameraShape1.fStop到liquidSurface2.fstop

  ---------------------------------------------------------------------
                              NOTES
  ---------------------------------------------------------------------
- liquidSurfaceShader 有些参数没有输出到rib文件里
  注意：参数如果是默认值，就不被输出到rib文件里。
  你可以更改参数的值，看看是否仍然没有输出到rib文件里


- 自定义shader里string类型参数的命名限制。
  对于自定义shader（比如liquidSurfaceShader）参数列表里的string类型参数(string a, string b)。
   - 如果该参数制定纹理名(string a="/texturepath/a.tex"),
     则需要将参数名加上前缀“texname”（string texnamea="/texturepath/a.tex"）
   - 如果该参数不指定纹理(string b="teststr"),
     则该参数名一定不能有“texname”前缀。
     如果有“texname”前缀，比如定义了(string texnameb="teststr")，同时texnameb不是纹理名或纹理路径，
     那么liquid会将string texnameb="teststr.tex"输出到rib文件里，造成错误。
    see liqShader.cpp line306 for more details.
    // [2/1/2012 yaoyansi]
    // This is a restriction in liquid(maya2renderer).
    // - If the attribute name starts with 'texname',(e.g. texname, texname0, texname_0, and etc.)
    //   it is a texture name or texture full path, 
    //   so we MUST append '.tex' to the plug value.
    // - If the plug is not a texture name or texture full path,
    //   DO NOT let the attribute name starts with 'texname'.
   - 字符串里不能包含'|'(即$gSeperator)字符


- *.pl 文件里matrix array没有实现


- 每次更新Maya.env后，需要相应更新liquid_\test\image_diff\testall.py里configMayaEnv()的环境变量ELVISHRAY_BIN的值
- 每次更细ER后
  - ER binary files(*.lib/*.dll/*.exe)所在的路径是否改变了，如果改变了，则需要更改：
    - eiSHADER_maya.sln里link lib的路径， post build event里的路径
    - liquid.sln里link的路径
    - liquid_\2.3.3\bin\Maya.env里ELVISHRAY_BIN的路径，并把Maya.env考到E:\MyDocuments\maya\2009\Maya.env
      同时更新liquid_\test\image_diff\testall.py里configMayaEnv()的环境变量ELVISHRAY_BIN的值
    - Maya2009\bin\manager.ini里searchpath的路径
  - 编译er，编译eiSHADER_maya.sln，编译liquid.sln


- 设置帧序列时，一定要记得把Animation选项勾上，否则只输出当前帧。


- maya_phong 里判断transparency是否为0：if ( almost_zerov( &transparency(), 0.001f ) )


- may file node
  - num_channels暂不考虑，以后判断texture file是否是单通道纹理后，参照3delight的实现再修改
  - 若干输入参数没有用到，以后参照3delight的实现再修改
  - color_texture/scalar_texture的参数dsdx, dsdy, dtdx, dtdy不知道如何设置
  - liquid里  ei_make_texture(..., ..., eiInt swrap, eiInt twrap,
	eiInt filter, eiScalar swidth, eiScalar twidth);时这几个参数如何设置

- Bump channel in Phong shader(for er)
  I make a hack to achieve the bump effect.The following steps will deliver (bump)file.outColor to phong.normalCamera
  - create bump2d.bumpNormal
  - file.outColor --> bump2d.bumpNormal
  - set bump2d.bumpInterp=2
  - in maya_bump2d: if(bumpInterp==2) outNormal()=bumpNormal();
  todo: 
  - delete bump2d.bumpNormal
  - recover bump2d.bumpInterp


- vertex normal 
  - smooth normal, like a sphere: fnMesh.getVertexNormal(vertex i, false, normal, MSpace::kObject)
  - sharp edge, like a cube
    in this case, like a cube, a vertex has a specified normal corresponding to each adjacent polygon.
    but elvishray's only allow a vertex to be assigned only one normal.
    so I can't generate the normal list for this case.


- place2dTexture
  - repeatUV is an output plug, so it is not set in OutputHelper::addRSLVariable()
    but repeatUV is set in maya directly. So repeateUV must be set manully. see RSL::Visitor::visitPlace2dTexture()

  ---------------------------------------------------------------------
                              F.A.Q.
  ---------------------------------------------------------------------
- Q: $(LiquidRoot)\2.3.3\renderers\*.lg 文件是什么?
  A:renderman是一个标准，支持这个标准的渲染器有prman，aqsis，3dlight等，
    lg文件就是用来配置prman，aqsis，3dlight各自的参数的
  
  Q:Aqsis和prman在我们项目里起的作用是什么
  A:liquid里用到aqsis的ribout模块，以输出rib文件
