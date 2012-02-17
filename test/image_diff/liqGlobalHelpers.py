# implement several funtions in liqGlobalHelpers.cpp
import sys
import os
import maya.standalone
import maya.OpenMaya as OpenMaya
import maya.cmds as cmds


def liquidTransGetSceneName():
    fullName = OpenMaya.MGlobal().executeCommandStringResult( "file -q -sn -shn" )
    if( len(fullName)==0 ):
        fullName = "untitled.mb"
    i = fullName.rfind( '/' )
    j = fullName.rfind( '.' )
    if(( j < i + 2 ) or ( j == -1 ) ):
        j = len(fullName)

    return fullName[(i + 1):(j)]
