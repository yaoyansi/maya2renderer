import sys
import os
import maya.standalone
import maya.OpenMaya as OpenMaya
import maya.cmds as cmds
import testone_by_mayapy as MyTestOne
import liqTestLog as mLiqlog


def configMayaEnv():
    #liquid maya
    os.environ["LIQUID_ROOT"]    = "E:/dev/autodesk/maya/myplugin/project/liquid_"
    os.environ["LIQUID_MEL"]     = os.environ["LIQUID_ROOT"]+"/2.3.3/mel"
    os.environ["LIQUID_ER_MEL"]  = os.environ["LIQUID_ROOT"]+"/2.3.3/src/elvishray/mel"
    os.environ["LIQUID_LUX_MEL"] = os.environ["LIQUID_ROOT"]+"/2.3.3/src/luxrenderer/mel"
    os.environ["LIQUID_GEN"]     = os.environ["LIQUID_ROOT"]+"/2.3.3/lib/plugins"
    os.environ["LIQUID_MLL"]     = os.environ["LIQUID_ROOT"]+"/2.3.3/bin/prman/win32"
    os.environ["LIQUID_ICON"]    = os.environ["LIQUID_ROOT"]+"/2.3.3/icons"
    os.environ["LIQUIDHOME"]     = os.environ["LIQUID_ROOT"]+"/2.3.3"
    os.environ["LIQUID_GLOBALS_OVERRIDE"] = os.environ["LIQUID_ROOT"]+"/2.3.3/renderers"
    #elvishray
    os.environ["ELVISHRAY_BIN"] = os.environ["LIQUID_ROOT"]+"/dependence/elvishray/bin"
    
    # PATH
    os.environ["PATH"] = os.environ["ELVISHRAY_BIN"]+";"+os.environ["PATH"]
    # MAYA_SCRIPT_PATH
    if os.environ.get('MAYA_SCRIPT_PATH') == None:
        os.environ["MAYA_SCRIPT_PATH"] =os.environ["LIQUID_ER_MEL"]+";"+os.environ["LIQUID_LUX_MEL"]+";"+os.environ["LIQUID_GEN"]+";"+os.environ["LIQUID_MEL"];
    else:
        os.environ["MAYA_SCRIPT_PATH"] =os.environ["LIQUID_ER_MEL"]+";"+os.environ["LIQUID_LUX_MEL"]+";"+os.environ["LIQUID_GEN"]+";"+os.environ["LIQUID_MEL"]+";"+os.environ["MAYA_SCRIPT_PATH"];
    # MAYA_PLUG_IN_PATH
    if os.environ.get('MAYA_PLUG_IN_PATH') == None:
        os.environ["MAYA_PLUG_IN_PATH"]=os.environ["LIQUID_MLL"]
    else:
        os.environ["MAYA_PLUG_IN_PATH"]=os.environ["LIQUID_MLL"]+";"+os.environ["MAYA_PLUG_IN_PATH"]
    # XBMLANGPATH
    if os.environ.get('MAYA_PLUG_IN_PATH') == None:
        os.environ["XBMLANGPATH"]=os.environ["LIQUID_ICON"]
    else:
        os.environ["XBMLANGPATH"]=os.environ["LIQUID_ICON"]+";"+os.environ["XBMLANGPATH"]
    #
    os.environ["MAYA_LOCATION"] = "D:/Program Files/Autodesk/Maya2009"
    os.environ["MAYA_PATH2009"] = "D:/Program Files/Autodesk/Maya2009"
    os.environ["PYTHONHOME"]    = "D:/Program Files/Autodesk/Maya2009/Python"
    os.environ["PYTHONPATH"]    = "D:/Program Files/Autodesk/Maya2009/bin/python25.zip;D:/Program Files/Autodesk/Maya2009/Python/lib/site-packages;"



def initialize():
    try:
        maya.standalone.initialize( name='python' )
    except:
        sys.stderr.write( "Failed in initialize standalone application" )
        raise



def test_all_scene():
    LIQUID_ROOT="E:/dev/Autodesk/maya/myplugin/project/liquid_"

    #testFile=LIQUID_ROOT+"/2.3.3/test/test_motionblur/transform/deform.ma"
    #MyTestOne.test_one_scene(testFile, "")

    testFile=LIQUID_ROOT+"/2.3.3/test/test_rm_texture/check10_tex.ma"
    MyTestOne.test_one_scene(testFile, "renderman")


def main():
    configMayaEnv()
    mLiqlog.flog("configMayaEnv() done.")
    initialize()
    mLiqlog.flog("initialize() done.")

    mLiqlog.flog("test_all_scene() begin.")
    test_all_scene()
    mLiqlog.flog("test_all_scene() end.")
    #raw_input("test_all_cases() done. Press ENTER to exit")


if __name__ == '__main__':
    main()
    #test_getStanderImage()
#_render_bat(testFile, "renderman")
#