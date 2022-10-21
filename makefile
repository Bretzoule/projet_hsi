CC = gcc
CFLAGS = -Wall -pedantic -I $(INCLUDEDIR)
LDFLAGS = -lm
RM = rm -rf
SRC = $(wildcard $(SRCDIR)*.c)
STATIC = $(wildcard $(SRCDIR)*.a)
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
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(STATIC)

$(BINDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS)  -c $^ -o $@ $(LDFLAGS)
	
.PHONY: clean
clean :
	$(RM) $(OBJ) core

.PHONY: save
save : savehead
	$(CP) $(SRC) $(SAVEDIR)
savehead: 
	$(CP) $(HEAD) $(SAVEDIR)

.PHONY: mrproper
mrproper :
	$(RM) -f $(BINDIR)* $(DOCDIR)html/ $(DOCDIR)latex/ $(SAVEDIR)*
	
.PHONY: doxy
doxy:
	doxygen ./doc/Doxyfile && firefox ./doc/html/index.html