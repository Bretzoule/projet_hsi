CC = gcc
CFLAGS = -Wall -pedantic -Iinclude
LDFLAGS = -lm
RM = rm -rf
SRC = $(wildcard $(srcdir)*.c)
HEAD = $(wildcard $(includedir)*.h)
STATIC = $(wildcard $(includedir)*.a)
OBJ = $(subst $(srcdir), $(bindir),$(SRC:.c=.o))
PROG = $(bindir)projet
srcdir = ./src/
docdir = ./doc/
bindir = ./bin/
savedir = ./save/
includedir = ./include/
CP = cp

all: $(PROG)
$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

./bin/%.o : ./src/%.c
	$(CC) $(CFLAGS)  -c $^ -o $@ $(LDFLAGS)
	
.PHONY: clean
clean :
	$(RM) $(OBJ) core


.PHONY: buildTypes
buildTypes :
	node ./script/index.js

.PHONY: save
save : savehead
	$(CP) $(SRC) $(savedir)
savehead: 
	$(CP) $(HEAD) $(savedir)

.PHONY: mrproper
mrproper :
	$(RM) -f $(bindir)* $(docdir)html/ $(docdir)latex/ $(savedir)*
	
.PHONY: doxy
doxy:
	doxygen ./doc/Doxyfile && firefox ./doc/html/index.html
