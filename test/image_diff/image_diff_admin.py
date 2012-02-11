import Image
import ImageChops
import hashlib
import sys
import os


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


#fileA="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12.bmp"
#fileB="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12_2.bmp"
#diffFile="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/dif_12_12.bmp"
fileA="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12.bmp"
fileB="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check15.bmp"
diffFile="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/dif_12_15.bmp"

def getDiffImageName(fileFullPath):
    diff_postfix="_diff";
    dot_i=fileFullPath.rfind('.')
    fileFullPath_withoutExt = fileFullPath[ 0 : dot_i ]
    fileExt = fileFullPath[(dot_i+1):]
    return (fileFullPath_withoutExt+diff_postfix+"."+fileExt)


def _compare(filenameA, filenameB):
    dataA = open(filenameA, 'rb').read()
    dataB = open(filenameB, 'rb').read()

    if hashlib.md5(dataA).hexdigest() != hashlib.md5(dataB).hexdigest():
        imageA = Image.open(filenameA)
        imageB = Image.open(filenameB)
        diff = ImageChops.difference(imageA, imageB)
        
        diffFilename = getDiffImageName(filenameA)
        diff.save( diffFilename )
        print("diff image has been output to:\n"+diffFilename+"\n");
    else:
        print("two images are equal.\n.")

    raw_input("_compare() done. Press ENTER to exit")


def _render_bat(mayaFile, liqRenderer):
    batchRenderCmd="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/my_mayabatch.bat"
    cmd = batchRenderCmd+' '+mayaFile+' '+liqRenderer;
    import os
    print("cmd="+cmd)
    os.system(cmd)

def _render(mayaFile, liqRenderer):
    #batchRenderCmd=""" "D:\\Program\ Files\\Autodesk\\Maya2009\bin\mayabatch.exe" """
    batchRenderCmd="mayabatch.exe ";
    command = """ "source \\"registerLiquidRenderer.mel\\"; registerLiquidRenderer(); setAttr -type \\"string\\" liquidGlobals.renderer """+liqRenderer+"""; mayaBatchRenderProcedure(0,\\"\\",\\"\\",\\"liquid\\",\\"\\");" """;
    cmd = batchRenderCmd+" -file "+mayaFile+" -command "+command;
    import os
    print("cmd="+cmd)
    os.system(cmd)


configMayaEnv()

LIQUID_ROOT="E:/dev/Autodesk/maya/myplugin/project/liquid_"
testFile=LIQUID_ROOT+"/2.3.3/test/test_motionblur/transform/deform.ma";
#_render_bat(testFile, "renderman")
#_render(testFile, "elvishray")
_render(testFile, "renderman")
raw_input("_render() done. Press ENTER to exit")
