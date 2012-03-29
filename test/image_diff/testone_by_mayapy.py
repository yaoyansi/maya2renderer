import sys
import os
import maya.standalone
import maya.OpenMaya as OpenMaya
import maya.cmds as cmds
import liqGlobalHelpers as gHelper
import liqTestLog as mLiqlog

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
        strdata = strinfo.sub( gHelper.liquidTransGetSceneName(), strdata)

    if strdata.find('$IMG')!=-1:
        strinfo = re.compile('\$IMG')
        strdata = strinfo.sub( cmds.getAttr('liquidGlobals.ddImageName[0]'), strdata)

    if strdata.find('$PDIR')!=-1:
        strinfo = re.compile('\$PDIR')
        strdata = strinfo.sub( cmds.workspace( q=True, dir=True ), strdata)

    if strdata.find('$RND')!=-1:
        strinfo = re.compile('\$RND')
        strdata = strinfo.sub( cmds.getAttr('liquidGlobals.renderer'), strdata)

    # TODO ...

    return strdata


def getOutputImageName(mayaFile, liqRenderer):
    cmds.file(mayaFile, force=True, open=True)
    cmds.setAttr('liquidGlobals.renderer', liqRenderer, type="string")
    output_image_name = parseString( cmds.getAttr('liquidGlobals.ddImageName[0]') )
    #cmds.file(save=True, force=True)
    return output_image_name


def getProjectDirectory(mayaFile):
    cmds.file(mayaFile, force=True, open=True)
    projectDir = cmds.workspace( q=True, fullName=True )
    #cmds.file(save=True, force=True)
    return projectDir+"/"


def getImageOutputDirectory(mayaFile):
    return getProjectDirectory(mayaFile)+"rmanpix/"

def getFileDirectory(mayaFile):
    slat_i=mayaFile.rfind('/')
    return mayaFile[ 0 : slat_i ]


def getStanderImage(mayaFile, liqRenderer):
    directory=getFileDirectory(mayaFile)
    imageName=getOutputImageName(mayaFile, liqRenderer)
    return (directory+"/output_img_std/"+imageName)


def _render(mayaFile, liqRenderer):
    batchRenderCmd="mayabatch.exe "
    command = """ "source \\"registerLiquidRenderer.mel\\"; registerLiquidRenderer(); setAttr -type \\"string\\" liquidGlobals.renderer """+liqRenderer+"""; mayaBatchRenderProcedure(0,\\"\\",\\"\\",\\"liquid\\",\\"\\");" """;
    cmd = batchRenderCmd+" -file "+mayaFile+" -command "+command;

    #mLiqlog.flog("batchRenderCmd="+cmd)
    os.system(cmd)


def _test(mayaFile, liqRenderer):
    mLiqlog.renderer_beg(liqRenderer)

    output_image_fullpath = getImageOutputDirectory(mayaFile)+getOutputImageName(mayaFile, liqRenderer)
    mLiqlog.output_img_beg(output_image_fullpath)
    mLiqlog.output_img_end()

    _render(mayaFile, liqRenderer)

    #import time
    #time.sleep(4)

    std_image_fullpath = getStanderImage(mayaFile, liqRenderer);
    import imagediff
    imagediff.compare(output_image_fullpath, std_image_fullpath)
    
    mLiqlog.renderer_end()
    raw_input("test \n<"+mayaFile+"> \nwith <"+liqRenderer+">  is done. \nPress ENTER to continue.")


def test_one_scene(mayaFile, liqRenderer):
    mLiqlog.scene_beg(mayaFile)
    if liqRenderer == "":
        _test(mayaFile, "elvishray")
        _test(mayaFile, "renderman")
    else:
        _test(mayaFile, liqRenderer)
    mLiqlog.scene_end()


def test_getStanderImage():
    configMayaEnv()
    initialize()
    print getStanderImage("E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/test/test_motionblur/transform/deform.ma", "renderman");
