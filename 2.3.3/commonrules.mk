debug : EXTRAFLAGS=-g -DDEBUG
debug : BIN_VERSION=debug
debug : VPATH=$(VPATHDEBUG)

#release : BIN_VERSION=release
newversion release : VPATH:=$(VPATHRELEASE)
newversion release : $(VPATH)


distdir :
	@mkdir -p $(DIST_DIR)

echovars :
	@echo AW_LOCATION $(AW_LOCATION)
	@echo MAYA_LOCATION $(MAYA_LOCATION)
	@echo MAYA_VERSIONS $(MAYA_VERSIONS)
	@echo OS_NAME $(OS_NAME)
	@echo FLAVORX $(FLAVORX)
	@echo LIQUIDSHORTVERSION $(LIQUIDSHORTVERSION)
	@echo BUILDDATE $(BUILDDATE)
	@echo LIQUIDVERSION $(LIQUIDVERSION)		
	@echo LIQRMAN $(LIQRMAN)		
	@echo LIQRMANPATH $(LIQRMANPATH)		
	@echo LIQRMANFLAGS $(LIQRMANFLAGS)		
	@echo LIQRMANLIBS $(LIQRMANLIBS)		
	@echo LIQWINRMANLIBS $(LIQWINRMANLIBS)		
	@echo USEDVAR $(USEDVAR)
	@echo PRMANVERSION $(PRMANVERSION)		
	@echo MAYA_VERSION $(MAYA_VERSION)

$(VPATHRELEASE) :
	@sh -c "if( test -d $(VPATHRELEASE) ); then \
		echo '$(VPATHRELEASE) already exists'; \
	else \
		echo 'creating $(VPATHRELEASE)'; \
		mkdir -p $(VPATHRELEASE); \
	fi;"

$(VPATHDEBUG) :
	@sh -c "if( test -d $(VPATHDEBUG) ); then \
		echo '$(VPATHDEBUG) already exists'; \
	else \
		echo 'creating $(VPATHDEBUG)'; \
		mkdir -p $(VPATHDEBUG); \
	fi;"

clean : VPATH?=$(VPATHDEBUG)
clean :
	rm -rf $(VPATH)/*.$(PLUGSUF) $(VPATH)/*.$(OBJEXT) $(VPATH)/*.d $(VPATH)/ii_files $(VPATH)/so_locations

cleandist : VPATH?=$(VPATHDEBUG)
cleandist :
	rm -rf $(VPATH)/*.$(OBJEXT) $(VPATH)/*.d $(VPATH)/ii_files
