utilsdir=$(CURDIR)/utils
VPATH:= $(VPATH):$(utilsdir):\
    $(utilsdir)/error:$(utilsdir)/init

SUBSRCS=
include $(utilsdir)/error/Makefile.inc
include $(utilsdir)/init/Makefile.inc
SRCS_UTILS:= $(SUBSRCS)

HEADERS+=elog.h