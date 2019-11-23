ifdef PROG
all:	localobj $(PROG) .dosomething
endif

YFLAGS= -d
RANLIB= touch
AROPT = crs

CURDIR:= $(shell pwd)
VPATH:= $(CURDIR)/$(objdir)

.PHONY:clean .dosomething localobject

clean:
	@if test -d $(objdir); then cd $(objdir); rm -f $(CLEANFILES) ;else true; fi;

localobj:
	@if test ! -d $(objdir); then mkdir $(objdir); else true; fi;

include $(MKDIR)/../Makefile.global
include $(MKDIR)/port/postgres.mk.$(PORTNAME)

define make_partial
	$(LD) -r -melf_i386 -o $(objdir)/$(@F) $(addprefix $(objdir)/,$(notdir $^))
endef

define cc_inobjdir
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(objdir)/$(<F) -o $(objdir)/$(@F)
endef

$(objdir)/%.o:%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(objdir)/$(@F)
