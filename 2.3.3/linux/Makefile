DEPTH = ..
BIN_VERSION ?= debug
include $(DEPTH)/commondefs.mk
VPATH ?= $(VPATHDEBUG)

# -lefence
#-llkm -lzip -ltarget
LIQUIDBINLIBS =		$(LIBS) $(MAYALIBS) \
					-lOpenMayalib \
					-lOpenMayaFX \
					-lAnimSlice \
					-lDeformSlice \
					-lDynSlice \
					-lKinSlice \
					-lModelSlice \
					-lNurbsSlice \
					-lPolySlice \
					-lProjectSlice \
					-lImage \
					-lShared \
					-lTranslators \
					-lDataModel \
					-lNurbsEngine \
					-lRenderModel \
					-lDependEngine \
					-lCommandEngine \
					-lFoundation \
					-lStringCatalog \
					-lIMF \
					-lAG \
					-lAnimEngine \
					-lAppVersion \
					-lGeometryEngine \
					-lDependCommand \
					-lExtensionLayer \
					-lPolyEngine \
					-lSubdivEngine \
					-lSubdivGeom \
					-l3dGraphics \
					-lNurbs \
					-lPoly \
					-lSubdiv \
					-lHWFoundation \
					-lHWGL \
					-lHWRender \
					-lBase \
					-lSharedUI \
					-lHWRenderMaya \
					-lDevices \
					-lManips \
					-lAnimUISlice \
					-lDynUISlice \
					-lRenderSlice \
					-lImageUI \
					-lModelUISlice \
					-lUrchinSlice \
					$(EXTRA_LIBS) \
					-lm

ifeq "$(MAYA_VERSION)" "8.0"
LIQUIDBINLIBS +=	-Wl,-rpath -Wl,$(MAYA_LOCATION)/lib \
					-lawxml2 \
					-lguide \
					-lsvml \
					-liff \
					-lm
endif

LIQUIDMAINOBJS = 	liqShader.$(OBJEXT) \
					liqAttachPrefAttribute.$(OBJEXT) \
					liqRibTranslator.$(OBJEXT) \
					liqRibParticleData.$(OBJEXT) \
					liqTokenPointer.$(OBJEXT) \
					liqWriteArchive.$(OBJEXT) \
					liqRibSurfaceData.$(OBJEXT) \
					liqPreviewShader.$(OBJEXT) \
					liqRibObj.$(OBJEXT) \
					liqRibNode.$(OBJEXT) \
					liqRibData.$(OBJEXT) \
					liqGlobalHelpers.$(OBJEXT) \
					liqRibNuCurveData.$(OBJEXT) \
					liqRibMeshData.$(OBJEXT) \
					liqRibLocatorData.$(OBJEXT) \
					liqRibClipPlaneData.$(OBJEXT) \
					liqRibCoordData.$(OBJEXT) \
					liqRibPfxData.$(OBJEXT) \
					liqRibPfxToonData.$(OBJEXT) \
					liqRibPfxHairData.$(OBJEXT) \
					liqRibLightData.$(OBJEXT) \
					liqRibHT.$(OBJEXT) \
					liqGetSloInfo.$(OBJEXT) \
					liqGetAttr.$(OBJEXT) \
					liqRibGenData.$(OBJEXT) \
					liqRibSubdivisionData.$(OBJEXT) \
					liqRibMayaSubdivisionData.$(OBJEXT) \
					liqProcessLauncher.$(OBJEXT) \
					liqRenderer.$(OBJEXT) \
					liqExpression.$(OBJEXT) \
					liqNodeSwatch.$(OBJEXT) \
					liqSurfaceNode.$(OBJEXT)	\
					liqDisplacementNode.$(OBJEXT)	\
					liqVolumeNode.$(OBJEXT)  \
					liqRibboxNode.$(OBJEXT)  \
					liqLightNode.$(OBJEXT)  \
					liqLightNodeBehavior.$(OBJEXT)\
					liqCoordSysNode.$(OBJEXT) \
					liqGlobalsNode.$(OBJEXT) \
					liqBucket.$(OBJEXT) \
					liqMayaRenderView.$(OBJEXT) \
					liqJobList.$(OBJEXT)


LIQUIDOUTMAINOBJS := $(patsubst %,$(VPATH)/%,$(LIQUIDMAINOBJS))



.SUFFIXES: .cpp .$(OBJEXT) .$(PLUGSUF) .c

LIQUIDPLUG := $(VPATH)/liquid.$(PLUGSUF)
LIQUIDBIN  := $(VPATH)/liquid
LIQUIDLIB  := $(VPATH)/libliquid.a
LIQUIDDPY  := $(VPATH)/$(LIQDPYNAME)

default: debug

#debug : EXTRAFLAGS=-g -DDEBUG
#debug : BIN_VERSION=debug
#release : BIN_VERSION=release

release newversion : $(VPATHRELEASE) $(LIQUIDPLUG) $(LIQUIDBIN) $(LIQUIDDPY)

debug : $(VPATHDEBUG) $(LIQUIDPLUG) $(LIQUIDBIN) $(LIQUIDDPY)

lib : $(VPATH) $(LIQUIDLIB)


liquidPlug : $(LIQUIDPLUG)

$(LIQUIDPLUG) : $(VPATH)/liquidPlug.$(OBJEXT) $(LIQUIDLIB)
	@echo $@
	$(CPP) $(LDFLAGS) -shared -o $(LIQUIDPLUG) $(VPATH)/liquidPlug.$(OBJEXT) $(LIQUIDLIB) $(LIBS)

$(LIQUIDBIN) : $(VPATH)/liquidBin.$(OBJEXT) $(LIQUIDLIB)
	@echo $@
	@$(CPP) -DLIQUIDBIN $(LDFLAGS) -o $(LIQUIDBIN) $(VPATH)/liquidBin.$(OBJEXT) $(LIQUIDLIB) $(LIQUIDBINLIBS)

$(LIQUIDLIB) : $(LIQUIDOUTMAINOBJS)
	@$(AR) $(LIQUIDLIB) $(LIQUIDOUTMAINOBJS)

ifneq "$(LIQRMAN)" "GENERIC"
$(LIQUIDDPY) : $(VPATH)/$(LIQDISPLAYOBJS).$(OBJEXT)
	@echo $@
	$(CPP) -shared $(VPATH)/$(LIQDISPLAYOBJS).$(OBJEXT) -I$(LIQRMANPATH) -L$(LIQRMANPATH)/lib -o $(LIQUIDDPY)
	mkdir -p ../$(LIQUIDDPYLOC)
	cp $(LIQUIDDPY) ../$(LIQUIDDPYLOC)
endif

$(LIQUIDOUTMAINOBJS) : ../include/liquid.h

ifneq "$(LIQRMAN)" "GENERIC"
$(VPATH)/$(LIQDISPLAYOBJS).$(OBJEXT) : $(LIQDISPLAYOBJS).cpp
	@echo "compiling > $@"
	$(CPP) -c $(DPYINCLUDES) $(INCLUDES) $(CPPFLAGS) -o $@ $<
endif

$(VPATH)/%.$(OBJEXT) : %.cpp
	@echo $@
	$(CPP) -c $(INCLUDES) $(CPPFLAGS) -o $@ $<

liqRibTranslator.o: ../include/liqRenderScript.h

.cpp.$(OBJEXT):
	@echo $@
	$(CPP) -c $(INCLUDES) $(CPPFLAGS) -o $(VPATH)/$@ $<

.cpp.i:
	@$(CPP) -E $(INCLUDES) $(CPPFLAGS) $*.cc > $(VPATH)/$*.i

depend:
	makedepend $(INCLUDES) -I/usr/include/CC liquid.cc

installpixie:
	@echo $(LIQUIDPLUG)
	@mkdir -p $(DESTDIR)/usr/share/liquid
	@mkdir -p $(DESTDIR)/usr/share/liquid/bin
	@cp -rf $(LIQUIDPLUG) $(DESTDIR)/usr/share/liquid/bin/liquid.so
	@mkdir -p $(DESTDIR)/usr/share/liquid/mel
	@cp -rf ../mel/*.mel $(DESTDIR)/usr/share/liquid/mel
	@cp -rf ../mel/*.png $(DESTDIR)/usr/share/liquid/mel
	@mkdir -p $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.xpm $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.iff $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.jpg $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/render_* $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/lif_* $(DESTDIR)/usr/share/liquid/icons
	@mkdir -p $(DESTDIR)/usr/share/liquid/renderers
	@cp -rf ../renderers/*.lg $(DESTDIR)/usr/share/liquid/renderers
	@mkdir -p $(DESTDIR)/usr/share/liquid/shaders
	@cp -rf $(VPATHSHADERS)/*.sdr $(DESTDIR)/usr/share/liquid/shaders
	@mkdir -p $(DESTDIR)/usr/share/liquid/shaders/src
	@cp -rf ../shaders/src/*.sl $(DESTDIR)/usr/share/liquid/shaders/src
	@mkdir -p $(DESTDIR)/usr/share/liquid/displayDrivers
	@mkdir -p $(DESTDIR)/usr/share/liquid/displayDrivers/Pixie
	@cp -rf $(LIQUIDDPY) $(DESTDIR)/usr/share/liquid/displayDrivers/Pixie/liqmaya.so

install3delight:
	@echo $(LIQUIDPLUG)
	@mkdir -p $(DESTDIR)/usr/share/liquid
	@mkdir -p $(DESTDIR)/usr/share/liquid/bin
	@cp -rf $(LIQUIDPLUG) $(DESTDIR)/usr/share/liquid/bin/liquid.so
	@mkdir -p $(DESTDIR)/usr/share/liquid/mel
	@cp -rf ../mel/*.mel $(DESTDIR)/usr/share/liquid/mel
	@cp -rf ../mel/*.png $(DESTDIR)/usr/share/liquid/mel
	@mkdir -p $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.xpm $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.iff $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.jpg $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/render_* $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/lif_* $(DESTDIR)/usr/share/liquid/icons
	@mkdir -p $(DESTDIR)/usr/share/liquid/renderers
	@cp -rf ../renderers/*.lg $(DESTDIR)/usr/share/liquid/renderers
	@mkdir -p $(DESTDIR)/usr/share/liquid/shaders
	@cp -rf $(VPATHSHADERS)/*.sdl $(DESTDIR)/usr/share/liquid/shaders
	@mkdir -p $(DESTDIR)/usr/share/liquid/shaders/src
	@cp -rf ../shaders/src/*.sl $(DESTDIR)/usr/share/liquid/shaders/src
	@mkdir -p $(DESTDIR)/usr/share/liquid/displayDrivers
	@mkdir -p $(DESTDIR)/usr/share/liquid/displayDrivers/3Delight
	@cp -rf $(LIQUIDDPY) $(DESTDIR)/usr/share/liquid/displayDrivers/3Delight/liqmaya.dpy

installair:
	@echo $(LIQUIDPLUG)
	@mkdir -p $(DESTDIR)/usr/share/liquid
	@mkdir -p $(DESTDIR)/usr/share/liquid/bin
	@cp -rf $(LIQUIDPLUG) $(DESTDIR)/usr/share/liquid/bin/liquid.so
	@mkdir -p $(DESTDIR)/usr/share/liquid/mel
	@cp -rf ../mel/*.mel $(DESTDIR)/usr/share/liquid/mel
	@cp -rf ../mel/*.png $(DESTDIR)/usr/share/liquid/mel
	@mkdir -p $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.xpm $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.iff $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/*.jpg $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/render_* $(DESTDIR)/usr/share/liquid/icons
	@cp -rf ../icons/lif_* $(DESTDIR)/usr/share/liquid/icons
	@mkdir -p $(DESTDIR)/usr/share/liquid/renderers
	@cp -rf ../renderers/*.lg $(DESTDIR)/usr/share/liquid/renderers
	@mkdir -p $(DESTDIR)/usr/share/liquid/shaders
	@cp -rf $(VPATHSHADERS)/*.sdb $(DESTDIR)/usr/share/liquid/shaders
	@mkdir -p $(DESTDIR)/usr/share/liquid/shaders/src
	@cp -rf ../shaders/src/*.sl $(DESTDIR)/usr/share/liquid/shaders/src
	@mkdir -p $(DESTDIR)/usr/share/liquid/displayDrivers
	@mkdir -p $(DESTDIR)/usr/share/liquid/displayDrivers/Air
	@cp -rf $(LIQUIDDPY) $(DESTDIR)/usr/share/liquid/displayDrivers/Air/d_liqmaya.so

clean : VPATH?=$(VPATHDEBUG)
clean :
	rm -rf $(VPATH)/*.$(PLUGSUF) $(VPATH)/*.$(OBJEXT) $(VPATH)/*.d $(VPATH)/ii_files $(VPATH)/so_locations

cleandist : VPATH?=$(VPATHDEBUG)
cleandist :
	rm -rf $(VPATH)/*.$(OBJEXT) $(VPATH)/*.d $(VPATH)/ii_files

include $(DEPTH)/commonrules.mk
