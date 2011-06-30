# Microsoft Developer Studio Project File - Name="liquid" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=liquid - Win32 Pixie Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "liquid.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "liquid.mak" CFG="liquid - Win32 Pixie Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "liquid - Win32 Pixie Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "liquid - Win32 Aqsis Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "liquid - Win32 3Delight Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "liquid - Win32 Prman Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "liquid - Win32 Pixie Generic ribLib Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "liquid - Win32 3Delight Generic ribLib Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "liquid - Win32 Aqsis Generic ribLib Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "liquid - Win32 Pixie Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_Pixie_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_Pixie_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/Pixie/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/Pixie/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "$(MAYA_LOCATION)/include" /I "$(DELIGHT)/include" /I "../include" /D "NDEBUG" /D "_3DELIGHT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIQUID_EXPORTS" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "$(PIXIEHOME)/include" /D "PIXIE" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /FD /Zm800 /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 3delight.lib libtarget.lib libzip.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib liblkm.lib ws2_32.lib netapi32.lib shell32.lib /nologo /dll /machine:I386 /nodefaultlib:"libmmt.lib" /nodefaultlib:"libircmt.lib" /out:"../bin/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"$(RMANTREE)/lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ri.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib /nologo /dll /incremental:yes /machine:I386 /out:"../../bin/Pixie/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"$(PIXIEHOME)/lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "liquid - Win32 Aqsis Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_Aqsis_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_Aqsis_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/Aqsis/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/Aqsis/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "$(PIXIEHOME)/include" /D "NDEBUG" /D "PIXIE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIQUID_EXPORTS" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm600 /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "$(AQSISHOME)/include" /D "AQSIS" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib ri.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib /nologo /dll /machine:I386 /nodefaultlib:"libmmt.lib" /nodefaultlib:"libircmt.lib" /out:"../../bin/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"$(PIXIEHOME)/lib"
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes
# ADD LINK32 ri2rib.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/Aqsis/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"$(AQSISHOME)/lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "liquid - Win32 3Delight Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_3Delight_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_3Delight_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/3Delight/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/3Delight/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "$(PIXIEHOME)/include" /D "NDEBUG" /D "PIXIE" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIQUID_EXPORTS" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm600 /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "$(DELIGHT)/include" /D "DELIGHT" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib ri.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib /nologo /dll /machine:I386 /nodefaultlib:"libmmt.lib" /nodefaultlib:"libircmt.lib" /out:"../../bin/Pixie/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"$(PIXIEHOME)/lib"
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes
# ADD LINK32 3delight.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib /nologo /dll /machine:I386 /out:"../../bin/3delight/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"$(DELIGHT)/lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "liquid - Win32 Prman Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_Prman_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_Prman_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/Pixie/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/Pixie/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../RILIB" /D "DELIGHT" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../RILIB" /D "PRMAN" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/3delight/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes
# ADD LINK32 zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/Prman/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "liquid - Win32 Pixie Generic ribLib Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_Pixie_Generic_ribLib_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_Pixie_Generic_ribLib_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/Pixie/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/Pixie/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../RILIB" /D "PIXIE" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /FD /Zm800 /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../ribLib" /D "PIXIE" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /FD /Zm800 /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 RILIB.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib /nologo /dll /incremental:yes /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/Pixie/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 RILIB.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib /nologo /dll /incremental:yes /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/Pixie/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "liquid - Win32 3Delight Generic ribLib Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_3Delight_Generic_ribLib_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_3Delight_Generic_ribLib_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/3Delight/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/3Delight/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../RILIB" /D "DELIGHT" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../ribLib" /D "DELIGHT" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/3delight/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes
# ADD LINK32 zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/3delight/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ELSEIF  "$(CFG)" == "liquid - Win32 Aqsis Generic ribLib Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "liquid___Win32_Aqsis_Generic_ribLib_Release"
# PROP BASE Intermediate_Dir "liquid___Win32_Aqsis_Generic_ribLib_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../bin/Aqsis/win32/Release/Objects"
# PROP Intermediate_Dir "../../bin/Aqsis/win32/Release/Objects"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../RILIB" /D "AQSIS" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../include" /I "$(MAYA_LOCATION)/include" /I "../../ribLib" /D "AQSIS" /D "MSVC6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_BOOL" /D ulong="unsigned long" /D uint="unsigned int" /D "_WIN32" /D "REQUIRE_IOSTREAM" /YX /FD /Zm800 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ri2rib.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/Aqsis/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT BASE LINK32 /pdb:none /incremental:yes
# ADD LINK32 RILIB.lib zdll.lib image.lib OpenMayaFX.lib Foundation.lib OpenMaya.lib OpenMayaRender.lib OpenMayaUI.lib OpenMayaAnim.lib shell32.lib glu32.lib opengl32.lib netapi32.lib ws2_32.lib RILIB.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcpmt.lib" /out:"../../bin/Aqsis/win32/Release/liquid.mll" /libpath:"$(MAYA_LOCATION)/lib" /libpath:"../../bin/win32lib"
# SUBTRACT LINK32 /pdb:none /incremental:yes

!ENDIF 

# Begin Target

# Name "liquid - Win32 Pixie Release"
# Name "liquid - Win32 Aqsis Release"
# Name "liquid - Win32 3Delight Release"
# Name "liquid - Win32 Prman Release"
# Name "liquid - Win32 Pixie Generic ribLib Release"
# Name "liquid - Win32 3Delight Generic ribLib Release"
# Name "liquid - Win32 Aqsis Generic ribLib Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\liqAttachPrefAttribute.cpp
# End Source File
# Begin Source File

SOURCE=..\liqBucket.cpp
# End Source File
# Begin Source File

SOURCE=..\liqCoordSysNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqDisplacementNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqExpression.cpp
# End Source File
# Begin Source File

SOURCE=..\liqGetAttr.cpp
# End Source File
# Begin Source File

SOURCE=..\liqGetSloInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\liqGlobalHelpers.cpp
# End Source File
# Begin Source File

SOURCE=..\liqGlobalsNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqJobList.cpp
# End Source File
# Begin Source File

SOURCE=..\liqLightNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqLightNodeBehavior.cpp
# End Source File
# Begin Source File

SOURCE=..\liqMayaRenderView.cpp
# End Source File
# Begin Source File

SOURCE=..\liqMemory.cpp
# End Source File
# Begin Source File

SOURCE=..\liqNodeSwatch.cpp
# End Source File
# Begin Source File

SOURCE=..\liqPreviewShader.cpp
# End Source File
# Begin Source File

SOURCE=..\liqProcessLauncher.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRenderer.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibboxNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibClipPlaneData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibCoordData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibGenData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibHT.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibLightData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibLocatorData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibMayaSubdivisionData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibMeshData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibNuCurveData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibObj.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibParticleData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibPfxHairData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibPfxToonData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibSubdivisionData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibSurfaceData.cpp
# End Source File
# Begin Source File

SOURCE=..\liqRibTranslator.cpp
# End Source File
# Begin Source File

SOURCE=..\liqShader.cpp
# End Source File
# Begin Source File

SOURCE=..\liqSurfaceNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqTokenPointer.cpp
# End Source File
# Begin Source File

SOURCE=..\liquidPlug.cpp
# End Source File
# Begin Source File

SOURCE=..\liqVolumeNode.cpp
# End Source File
# Begin Source File

SOURCE=..\liqWriteArchive.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\liqAttachPrefAttribute.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqBucket.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqCoordSysNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqCustomNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqDisplacementNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqExpression.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqGetAttr.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqGetSloInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqGlobalHelpers.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqGlobals.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqGlobalsNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqIOStream.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqLightNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqLightNodeBehavior.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqMayaRenderView.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqMemory.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqNodeSwatch.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqPreviewShader.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqProcessLauncher.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRenderer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRenderScript.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibBakeSubdivisionData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibboxNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibClipPlaneData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibCoordData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibCustomNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibGen.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibGenData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibHT.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibLightData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibLocatorData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibMayaSubdivisionData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibMeshData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibNuCurveData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibObj.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibParticleData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibPfxHairData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibPfxToonData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibSubdivisionData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibSurfaceData.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqRibTranslator.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqShader.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqSurfaceNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqTokenPointer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liquid.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqVolumeNode.h
# End Source File
# Begin Source File

SOURCE=..\..\include\liqWriteArchive.h
# End Source File
# Begin Source File

SOURCE=..\..\include\PixliqMayaDisplayDriverPixie.h
# End Source File
# Begin Source File

SOURCE=..\..\include\PixliqMayaRenderView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "MEL Scripts"

# PROP Default_Filter "*.mel"
# Begin Source File

SOURCE=..\mel\getMultiListerSelection.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidAttachParams.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidAttrWindow.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidConvMTOR.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidDelayedReadArchive.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidFileBrowser.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidFluid.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidGlobals.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidHelpers.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidMenuHelp.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidParamDialogWindow.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidPrefAttribute.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidReadArchive.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidReAttachParams.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidRibBox.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidRibGen.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidShaders.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidShutdown.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidStartup.mel
# End Source File
# Begin Source File

SOURCE=..\mel\liquidSubD.mel
# End Source File
# End Group
# End Target
# End Project
