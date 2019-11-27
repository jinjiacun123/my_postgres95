utilsdir=$(CURDIR)/utils
VPATH:= $(VPATH):$(utilsdir): \
    $(utilsdir)/error:$(utilsdir)/init: \
    $(utilsdir)/cache

SUBSRCS=
include $(utilsdir)/error/Makefile.inc
include $(utilsdir)/init/Makefile.inc
include $(utilsdir)/cache/Makefile.inc
SRCS_UTILS:= $(SUBSRCS)

GENFMGRTAB= $(utilsdir)/Gen_fmgrtab.sh
GENFMGRTABFILES= fmgrtab.c

$(GENFMGRTABFILES): $(GENFMGRTAB) $(catdir)/pg_proc.h
	cd $(objdir); \
    sh $(SHOPTS) $(GENFMGRTAB) $(

HEADERS+=elog.h 