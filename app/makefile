CC = gcc
CFLAGS = -Wall -pedantic -I $(INCLUDEDIR)
LDFLAGS = -lm
RM = rm -rf
SRC = $(wildcard $(SRCDIR)*.c)
INCLUDESTATIC = $(wildcard $(SRCDIR)*.a)
HEAD = $(wildcard $(INCLUDEDIR)*.h)
OBJ = $(subst $(SRCDIR), $(BINDIR),$(SRC:.c=.o))
PROG = $(BINDIR)app
SRCDIR = $(APPDIR)src/
DOCDIR = $(APPDIR)doc/
BINDIR = $(APPDIR)bin/
SAVEDIR = $(APPDIR)save/
INCLUDEDIR = $(APPDIR)include/
CP = cp

APP: $(PROG)

$(PROG): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(INCLUDESTATIC)

$(BINDIR)%.o : $(SRCDIR)%.c
	@$(CC) $(CFLAGS)  -c $^ -o $@ $(LDFLAGS)
	
.PHONY: clean
clean :
	@echo "Cleaning bin folder"
	@$(RM) $(OBJ) $(OBJSTATIC) core

.PHONY: save
save : savehead
	@$(CP) $(SRC) $(SAVEDIR)
savehead: 
	@$(CP) $(HEAD) $(SAVEDIR)

.PHONY: mrproper
mrproper :
	@echo "Cleaning everything"
	@$(RM) -f $(BINDIR)* $(DOCDIR)html/ $(DOCDIR)latex/ $(STATICDIR)
	
.PHONY: doxy
doxy:
	@doxygen $(DOCDIR)/Doxyfile && firefox $(DOCDIR)/html/index.html
