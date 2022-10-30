ROOTDIR=.
TOOLSDIR=$(ROOTDIR)tools/
APPDIR=$(ROOTDIR)/app/
STATICDIR=$(APPDIR)static/
RUN=run.sh


include $(APPDIR)makefile

include $(APPDIR)makefile_static

all: STATIC APP

.PHONY: runall
runall: preparerunall all
	@./$(ROOTDIR)/$(RUN)

.PHONY: preparerunall
preparerunall:
	@chmod +x $(ROOTDIR)/$(RUN)

.PHONY: cleanall
cleanall: cleangenerated mrproper