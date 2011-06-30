# Microsoft Developer Studio Project File - Name="RILIB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RILIB - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RILIB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RILIB.mak" CFG="RILIB - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RILIB - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../bin/win32lib/objs"
# PROP Intermediate_Dir "../../../bin/win32lib/objs"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "HAVE_ZLIB" /FD /c
# SUBTRACT CPP /X /u /YX
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../bin/win32lib/RILIB.lib"
# Begin Target

# Name "RILIB - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\ribLib\error.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\ri.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\ribOut.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\riInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\variable.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\ribLib\common.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\error.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\ri.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\ribOut.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\riInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\ribLib\variable.h
# End Source File
# End Group
# End Target
# End Project
