import sys
import os
import maya.standalone
import maya.OpenMaya as OpenMaya
import maya.cmds as cmds

import liqTestLog as mLiqlog
import mayaenv
import testscene

def initialize():
    try:
        maya.standalone.initialize( name='python' )
    except:
        sys.stderr.write( "Failed in initialize standalone application" )
        raise


def main():
    mayaenv.configMayaEnv()
    mLiqlog.flog("configMayaEnv() done.")
    initialize()
    mLiqlog.flog("initialize() done.")

    mLiqlog.flog("test_all_scene() begin.")
    testscene.test_all_scene()
    mLiqlog.flog("test_all_scene() end.")
    #raw_input("test_all_cases() done. Press ENTER to exit")


if __name__ == '__main__':
    main()
    #test_getStanderImage()
#_render_bat(testFile, "renderman")
#