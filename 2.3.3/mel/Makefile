# Common definition to compile shaders
DEPTH = ..
include $(DEPTH)/commondefs.mk


MELSCRIPTS := $(wildcard *.mel)
TARGETS = $(patsubst %.mel,$(VPATHMEL)/%.mel, $(MELSCRIPTS))

#BIN_VERSION=debug

.SUFFIXES :
.SUFFIXES : .slo .sl

all :


newversion : $(VPATHMEL) $(TARGETS)

$(VPATHMEL) :
	mkdir -p $@


$(VPATHMEL)/%.mel : %.mel
	@echo $@
	@$(CP) $< $@


include $(DEPTH)/commonrules.mk
