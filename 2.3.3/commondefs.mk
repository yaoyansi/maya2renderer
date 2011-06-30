SHELL = sh

#********************************************
# Set default if variables not set
#********************************************

AW_LOCATION ?= /usr/aw
MAYA_LOCATION ?= $(AW_LOCATION)/maya
MAYA_VERSIONS := $(wildcard $(AW_LOCATION)/maya*)
MAYA_VERSION ?= 7.0
LIQRMAN ?= pixie
LIQ_OLD_MAYA_IDS ?= 0
# Os settings
# What about Suze ?

OS_NAME := $(shell uname -o)

ifeq "$(OS_NAME)" "GNU/Linux"
PLUGSUF		= so
OBJEXT		= o
LD		= $(MAYA_LOCATION)/bin/mayald
LOCFLAGS	= -O3 -funroll-loops -march=pentiumpro -D_BOOL -DLINUX -DLIQ_OLD_MAYA_IDS=$(LIQ_OLD_MAYA_IDS)
WARNFLAGS	= -Wall -W -Wno-comment -Wpointer-arith -Wno-inline -Woverloaded-virtual -Wno-sign-compare -Wno-parentheses -Wno-deprecated
NO_TRANS_LINK	=
VBIN		= redhat
EXTRA_LIBS	=
AR		= ar cqs
CPP		= gcc

UX_RELEASE_TEST_FILES = /etc/fedora-release /etc/redhat-release /etc/slackware-version /etc/gentoo-release
UX_RELEASE_FILE ?= $(foreach FILE, $(UX_RELEASE_TEST_FILES), $(wildcard $(FILE)*))
FLAVORX := $(patsubst /etc/%-release,%,$(UX_RELEASE_FILE))
FLAVORX := $(patsubst /etc/%-version,%,$(FLAVORX))

#********************************************
# Anything special for some linux flavor ?
#********************************************
ifeq "$(FLAVORX)" "fedora redhat"
VBIN	= fedora
ifneq "$(MAYA_VERSION)" "8.0"
# Make sure we use gcc 3.3.4 if 3.4.4 is default one
ifeq "$(shell $(CPP) -dumpversion)" "3.4.4"
CPP = g++334
endif
else
CPP = g++
endif
else
VBIN	= $(FLAVORX)
endif

else
ifeq "$(OS_NAME)" "Cygwin"
# Cygwin
FLAVORX = cygwin
PLUGSUF			= .mll
BINSUF			= .exe
OBJSUF			= .obj
LIBSUF			= .lib
CPP			= cl
LINK			= link
LD			= $(MAYA_LOCATION)/bin/mayald
LOCFLAGS		= -nologo -O2 -EHsc -MT -YXstdafx.h -FD -GR -D_BOOL -D_WIN32 -DWIN32 -D_USRDLL -DLIQUID_EXPORTS -Dulong="unsigned long" -Duint="unsigned int"
WARNFLAGS		= -W1
VBIN			= win32
AR			= ar cqs
LINKEROPTS		= -INCREMENTAL:NO -NOLOGO -NODEFAULTLIB:libircmt$(LIBEXT) -PDB:liquid.pdb -MACHINE:I386
LIBPATHFLAG		= -LIBPATH:
LIBFLAG			=
SHAREDFLAG		= -DLL
OUTFLAG			= -Fo
EXTRALIBS		= $(LIBFLAG)shell32$(LIBSUF) $(LIBFLAG)Foundation$(LIBSUF)

endif

#********************************************
# Not Linux, not Cygwin ...what is it ?
#********************************************

FLAVORX = "notunix"
endif

ifeq "$(OS_NAME)" "Cygwin"
SPC = \040
else
SPC = " "
endif

LIQUIDSHORTVERSION := $(shell tr -d \"\\"\\"\" < $(DEPTH)/src/liquid.version)
BUILDDATE := $(shell date '+%d.$(SPC)%b.$(SPC)%Y$(SPC):$(SPC)%R')
LIQUIDVERSION = \"$(SPC)$(LIQUIDSHORTVERSION)$(SPC)for$(SPC)$(LIQRMAN),$(SPC)$(BUILDDATE)$(SPC)\"

# Renderers setting
# Pixie
ifeq "$(LIQRMAN)" "pixie"
LIQDISPLAYOBJS  = 	liqMayaDisplayDriverPixie
LIQRMANPATH 	= 	$${PIXIEHOME:=/usr/local/Pixie}
LIQUIDDPYLOC	=	displayDrivers/Pixie/
LIQDPYNAME	=	liqmaya.so
LIQRMANFLAGS	=	-DPIXIE
LIQRMANLIBS 	=	-lri -lsdr
LIQWINRMANLIBS	=	"ri.lib sdr.lib"
USEDVAR 	=	PIXIEHOME
CSL 		= 	$(LIQRMANPATH)/bin/sdrc
SLOEXT		=	sdr
SLFLAGS 	=
endif

ifeq "$(LIQRMAN)" "GENERIC"
USE_RIBLIB	= yes
LIQRMANFLAGS	= -DGENERIC_RIBLIB
LIQRMANLIBS	=
LIQDISPLAYOBJ	=
endif

#********************************************
# Renderers setting
# Air
#********************************************
ifeq "$(LIQRMAN)" "air"
USE_RIBLIB		:=	yes
LIQDISPLAYOBJS  = 	liqMayaDisplayDriverAir
LIQRMANPATH 	= 	$${AIRHOME:=/usr/local/Air}
LIQUIDDPYLOC	=	displayDrivers/Air/
LIQDPYNAME	=	d_liqmaya.so
LIQRMANFLAGS	=	-DAIR
LIQRMANLIBS 	=
LIQWINRMANLIBS	=
USEDVAR 	=	AIRHOME
CSL 		= 	$(LIQRMANPATH)/bin/shaded
SLOEXT		=	sdb
SLFLAGS 	=
endif

#********************************************
# Aqsis
#********************************************
ifeq "$(LIQRMAN)" "aqsis"
LIQDISPLAYOBJS  = 	liqMayaDisplayDriverAqsis
LIQRMANPATH 	=	$${AQSIS_BASE_PATH:=/usr/local/aqsis}
LIQUIDDPYLOC	=	displayDrivers/Aqsis/
LIQDPYNAME	=	liqmaya.so
LIQRMANFLAGS	=	-DAQSIS
LIQRMANLIBS 	=	-lshaderexecenv -lshadervm -laqsistypes -lri2rib -lslxargs
LIQWINRMANLIBS	=	ri2rib.lib slxargs.lib
USEDVAR 	=	AQSIS_BASE_PATH
CSL 		= 	$(LIQRMANPATH)/bin/aqsl
SLOEXT		=	slx
SLFLAGS 	= 	-DAQSIS
endif

#********************************************
# 3delight
#********************************************
ifeq "$(LIQRMAN)" "3delight"
LIQDISPLAYOBJS  =	liqMayaDisplayDriver3Delight
LIQRMANPATH 	=	$${DELIGHT:=/usr/local/3delight}
LIQUIDDPYLOC	=	displayDrivers/3Delight/
LIQDPYNAME	=	liqmaya.dpy
LIQRMANFLAGS	=	-DDELIGHT
LIQRMANLIBS 	=	-l3delight -lc -ldl -lm
LIQWINRMANLIBS	=	3delight.lib
USEDVAR 	=	DELIGHT
CSL 		= 	$(LIQRMANPATH)/bin/shaderdl
SLOEXT		=	sdl
SLFLAGS 	=	-DDELIGHT
endif

#********************************************
# Entropy
#********************************************
ifeq "$(LIQRMAN)" "entropy"
LIQDISPLAYOBJS  = 	liqMayaDisplayDriverEntropy
LIQRMANPATH 	=	$${ENTROPYHOME:=/usr/local/exluna/Entropy}
LIQUIDDPYLOC	=	displayDrivers/Entropy/
LIQDPYNAME	=	d_liqmaya.so
LIQRMANFLAGS	=	-DENTROPY
LIQRMANLIBS 	=	-lribout -lsleargs
USEDVAR 	=	ENTROPYHOME
CSL 		= 	$(LIQRMANPATH)/bin/sle
SLOEXT		=	fixme
SLFLAGS 	= 	-DENTROPY
endif

#********************************************
# Prman
#********************************************
ifeq "$(patsubst prman%,prman,$(LIQRMAN))" "prman"
PRMANVERSION 	= 	$(patsubst prman%,%,$(LIQRMAN))
LIQRMANPATH 	=	$${RMANTREE:=/usr/local/prman}
LIQUIDDPYLOC	=	displayDrivers/PRMan/
LIQDPYNAME	=	d_liqmaya.so
LIQRMANFLAGS	=	-DPRMAN
USEDVAR 	= 	RMANTREE
CSL 		= 	$(LIQRMANPATH)/bin/shader
SLFLAGS 	= 	-DPRMAN
SLOEXT		=	slo
LIQDISPLAYOBJS  = 	liqMayaDisplayDriver

ifeq "$(patsubst 12.%,12,$(PRMANVERSION))" "12"
LIQRMANLIBS 	=	-lrib -lsloargs -llkm -ltarget -lzip -lprmutil
LIQWINRMANLIBS	= "rib.lib sloargs.lib"
LIQUIDDPYLOC	=	displayDrivers/PRMan/
else
ifeq "$(patsubst 13.%,13,$(PRMANVERSION))" "13"
LIQRMANLIBS 	=	-lprmansdk
LIQWINRMANLIBS	=	prmansdk.lib
LIQUIDDPYLOC	=	displayDrivers/PRMan/
else
LIQRMANLIBS=-lrib -lsloargs -llkm -ltarget -lzip
LIQWINRMANLIBS	=	rib.lib sloargs.lib
endif

endif

endif



INSTALL_DIR  = /temp/maya$(MAYA_VERSION)/liquid
#INSTALL_DIR  = /net/soft/fscfc/maya$(MAYA_VERSION)/liquid
INSTALL_PLUG_DIR = /temp/maya$(MAYA_VERSION)/liquid

LIQ_ICONS_DIR   	= $(INSTALL_DIR)/icons
LIQ_SHADERS_SRC_DIR = $(INSTALL_DIR)/shaders/src
LIQ_SHADERS_DIR 	= $(INSTALL_DIR)/shaders
LIQ_RENDERERS_DIR 	= $(INSTALL_DIR)/renderers

#BIN_VERSION 		?= $(LIQUIDSHORTVERSION)
VPATHDEBUG		= $(DEPTH)/bin/$(VBIN)/debug/$(LIQRMAN)/$(MAYA_VERSION)
VPATHRELEASE		= $(DEPTH)/bin/$(VBIN)/$(BIN_VERSION)/$(LIQRMAN)/$(MAYA_VERSION)
VPATH			?= $(DEPTH)/bin/$(VBIN)/$(BIN_VERSION)/$(LIQRMAN)/$(MAYA_VERSION)
VPATHSHADERS 		= $(DEPTH)/bin/$(VBIN)/$(BIN_VERSION)/$(LIQRMAN)/shaders
VPATHMEL 		= $(DEPTH)/bin/$(VBIN)/$(BIN_VERSION)/$(LIQRMAN)/mel
VPATHRENDERS 		= $(DEPTH)/bin/$(VBIN)/$(BIN_VERSION)/$(LIQRMAN)/renderers
VPATHICONS  		= $(DEPTH)/bin/$(VBIN)/$(BIN_VERSION)/$(LIQRMAN)/icons
CPPFLAGS		= -DLIQUIDVERSION=$(LIQUIDVERSION) $(LOCFLAGS) $(LIQRMANFLAGS) $(WARNFLAGS) $(EXTRAFLAGS) $(NO_TRANS_LINK) -DREQUIRE_IOSTREAM
LDFLAGS			= $(CPPFLAGS) -L$(MAYA_LOCATION)/lib -L$(LIQRMANPATH)/lib -L/usr/lib

ifeq "$(USE_RIBLIB)" "yes"
INCLUDES		= -I. -I.. -I$(MAYA_LOCATION)/include -I$(DEPTH)/ribLib -I../include
LIBS			= $(DEPTH)/bin/linux32/librib.a $(MAYALIBS) $(EXTRA_LIBS) -lm -lz
CPPFLAGS 		+= -DGENERIC_RIBLIB
else
INCLUDES		= -I. -I.. -I$(MAYA_LOCATION)/include -I$(LIQRMANPATH)/include -I../include
LIBS			= $(LIQRMANLIBS) $(MAYALIBS) $(EXTRA_LIBS) -lm
endif

DPYINCLUDES		= -I$(LIQRMANPATH)/include

ifeq "$(MAYA_VERSION)" "8.0"
MAYALIBS		= -lOpenMaya -lOpenMayaRender -lOpenMayaUI -lOpenMayaAnim -lOpenMayaFX -lGL -lGLU
else
MAYALIBS		= -lOpenMaya -lOpenMayaRender -lOpenMayaUI -lOpenMayaAnim -lOpenMayaFX -lxpcom -lGL -lGLU
endif

TARGET  		= $(VPATH)/$(LIQUIDPLUG)

CP 		= cp
