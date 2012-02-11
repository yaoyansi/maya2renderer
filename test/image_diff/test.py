import maya.standalone
import maya.OpenMaya as OpenMaya

import sys

def main( argv = None ):
    try:
        maya.standalone.initialize( name='python' )
    except:
        sys.stderr.write( "Failed in initialize standalone application" )
        raise

    sys.stderr.write( "Hello world! (script output)\n" )
    OpenMaya.MGlobal().executeCommand( "print \"Hello world! (command script output)\\n\"" )
        
#if __name__ == "__main__":
main()

import maya.cmds as cmds
cmds.batchRender("E:/dev/Autodesk/maya/myplugin/project/liquid_/2.3.3/test/test_motionblur/transform/transform.ma")
print("batch render done.\n");
raw_input("Press ENTER to exit")


def getDiffImageName(fileFullPath):
    diff_postfix="_diff";
    dot_i=fileFullPath.rfind('.')
    fileFullPath_withoutExt = fileFullPath[ 0 : dot_i ]
    fileExt = fileFullPath[(dot_i+1):]
    return (fileFullPath_withoutExt+diff_postfix+"."+fileExt)

fileFullPath="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12.bmp"
diffFile=getDiffImageName(fileFullPath)

print("diffFile="+diffFile+"\n")

raw_input("Press ENTER to exit")