import sys
import os
import maya.standalone
import maya.OpenMaya as OpenMaya
import maya.cmds as cmds

def init():
    try:
        maya.standalone.initialize( name='python' )
    except:
        sys.stderr.write( "Failed in initialize standalone application" )
        raise
#    sys.stderr.write( "Hello world! (script output)\n" )
#    OpenMaya.MGlobal().executeCommand( "print \"Hello world! (command script output)\\n\"" )



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
    os.environ["ELVISHRAY_BIN"] = os.environ["LIQUID_ROOT"]+"/dependence/elvishray/trunk/build/r1008/x86_Debug"
    
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


def parseString(strdata):
    import maya.cmds as cmds
    import re

    if strdata.find('$CAM')!=-1:
        strinfo = re.compile('\$CAM')
        strdata = strinfo.sub(cmds.getAttr('liquidGlobals.renderCamera'), strdata )

    if strdata.find('$F')!=-1:
        strinfo = re.compile('\$F')
        frame = "%d" % cmds.currentTime( query=True ) 
        strdata = strinfo.sub( frame, strdata)

    if strdata.find('$SCN')!=-1:
        strinfo = re.compile('\$SCN')
        strdata = strinfo.sub( cmds.getAttr('liquidGlobals.ribName'), strdata)

    if strdata.find('$IMG')!=-1:
        strinfo = re.compile('\$IMG')
        strdata = strinfo.sub( cmds.getAttr('liquidGlobals.ddImageName[0]'), strdata)

    if strdata.find('$PDIR')!=-1:
        strinfo = re.compile('\$PDIR')
        strdata = strinfo.sub( cmds.workspace( q=True, dir=True ), strdata)

    if strdata.find('$RND')!=-1:
        strinfo = re.compile('\$RND')
        strdata = strinfo.sub( cmds.getAttr('liquidGlobals.renderer'), strdata)

    return strdata

def getOutputImage(mayaFile)
	cmds.file(mayaFile, force=True, open=True)
        output_image = parseString( cmds.getAttr('liquidGlobals.ddImageName[0]') )
        output_image_fullpath = cmds.workspace( q=True, dir=True )+"rmanpix/"+output_image;
        cmds.file(save=True, force=True)
	return output_image_fullpath

def _render(mayaFile, liqRenderer):
    try:
        configMayaEnv()
        maya.standalone.initialize( name='python' )

        output_image_fullpath = getOutputImage(mayaFile)
        print("output_image="+output_image_fullpath+"\n")

    except:
        sys.stderr.write( "Failed in initialize standalone application" )
        raise
    #print( sys.path )
    
    import os
   
    batchRenderCmd="mayabatch.exe "
    command = """ "source \\"registerLiquidRenderer.mel\\"; registerLiquidRenderer(); setAttr -type \\"string\\" liquidGlobals.renderer """+liqRenderer+"""; mayaBatchRenderProcedure(0,\\"\\",\\"\\",\\"liquid\\",\\"\\");" """;
    cmd = batchRenderCmd+" -file "+mayaFile+" -command "+command;

    print("cmd="+cmd)
    os.system(cmd)


LIQUID_ROOT="E:/dev/Autodesk/maya/myplugin/project/liquid_"
testFile=LIQUID_ROOT+"/2.3.3/test/test_motionblur/transform/deform.ma"
#_render_bat(testFile, "renderman")
_render(testFile, "elvishray")

#raw_input("_render() done. Press ENTER to exit")
