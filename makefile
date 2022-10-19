ROOTDIR=./
TOOLSDIR=$(ROOTDIR)tools/
APPDIR=$(ROOTDIR)app/

include $(APPDIR)/makefile

all: APP

.PHONY: runall
runall: rundriver runapp


.PHONY: runapp
runapp:
	$(bindir)$(PROGNAME)


.PHONY: rundriver
rundriver:
	./tools/driver &


