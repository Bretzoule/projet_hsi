ROOTDIR=.
TOOLSDIR=$(ROOTDIR)tools/
APPDIR=$(ROOTDIR)/app/
STATICDIR=$(APPDIR)static/
SCRIPTDIR=$(ROOTDIR)/script/
RUN=run.sh
NODE=node
generator_exec=$(SCRIPTDIR)index.js

include $(APPDIR)makefile

include $(APPDIR)makefile_static.mk

all: GENERATOR STATIC APP

GENERATOR:
	@echo "Generating static"
	@$(NODE) $(generator_exec)

.PHONY: runall
runall: preparerunall
	@./$(ROOTDIR)/$(RUN)

.PHONY: preparerunall
preparerunall:
	@chmod +x $(ROOTDIR)/$(RUN)
	
.PHONY: cleanall
cleanall: cleangenerated mrproper