import sys
import os
import hashlib


fileA="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12.bmp"
fileB="E:/dev/Autodesk/maya/myplugin/project/liquid_/test/image_diff/check12_m.bmp"

def getDiffImageName(fileFullPath):
    diff_postfix="_diff";
    dot_i=fileFullPath.rfind('.')
    fileFullPath_withoutExt = fileFullPath[ 0 : dot_i ]
    fileExt = fileFullPath[(dot_i+1):]
    return (fileFullPath_withoutExt+diff_postfix+"."+fileExt)

def doDiff(filenameA, filenameB, diffFileName):
    cmd=".\\ImageMagick_6.7.5_Q16\\compare.exe "+filenameA+' '+filenameB+' '+diffFileName
    print("cmd="+cmd+"\n")
    os.system(cmd)


def _compare(filenameA, filenameB):
    dataA = open(filenameA, 'rb').read()
    dataB = open(filenameB, 'rb').read()

    return (hashlib.md5(dataA).hexdigest() == hashlib.md5(dataB).hexdigest())==True


def compare(filenameA, filenameB):
    print("compare("+filenameA+","+filenameB+")\n")
    if _compare(filenameA, filenameB)==True:
        print("two images are equal.\n.")
    else:
        diffFileName = getDiffImageName(filenameA)
        doDiff( filenameA, filenameB, diffFileName )
        print("diff image has been output to:\n"+diffFileName+"\n")