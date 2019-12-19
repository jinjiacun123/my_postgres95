utilsdir=$(CURDIR)/utils
VPATH:= $(VPATH):$(utilsdir): \
    $(utilsdir)/error:$(utilsdir)/init: \
    $(utilsdir)/cache:$(utilsdir)/mmgr: \
    $(utilsdir)/adt:$(utilsdir)/hash

SUBSRCS=
include $(utilsdir)/adt/Makefile.inc
include $(utilsdir)/mmgr/Makefile.inc
include $(utilsdir)/error/Makefile.inc
include $(utilsdir)/cache/Makefile.inc
include $(utilsdir)/hash/Makefile.inc
include $(utilsdir)/init/Makefile.inc
SRCS_UTILS:= $(SUBSRCS)

GENFMGRTAB= $(utilsdir)/Gen_fmgrtab.sh
GENFMGRTABFILES= fmgrtab.c

$(GENFMGRTABFILES): $(GENFMGRTAB) $(catdir)/pg_proc.h
	cd $(objdir); \
    sh $(SHOPTS) $(GENFMGRTAB) $(BKIOPTS) $(catdir)/pg_proc.h       

POSTGRES_DEPEND+= ${GENFMGRTABFILES}



HEADERS+=elog.h mcxt.h builtins.h relcache.h hsearch.h tqual.h