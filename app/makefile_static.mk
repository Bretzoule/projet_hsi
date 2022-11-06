OBJSTATIC = $(subst $(STATICDIR), $(BINDIR),$(SRCSTATIC:.c=.o))
SRCSTATIC = $(wildcard $(STATICDIR)*.c)
STATICLIB = $(SRCDIR)types.a

STATIC: $(STATICLIB)

$(STATICLIB): $(OBJSTATIC)
	@ar rcs $@ $^
	@make clean
	@cp $(STATICDIR)*.h $(INCLUDEDIR)

$(BINDIR)%.o: $(STATICDIR)%.c $(STATICDIR)%.h 
	@$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: cleangenerated
cleangenerated:
	@echo "Removing generated files."
	@$(RM) $(STATICLIB)