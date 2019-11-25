utilsdir=$(CURDIR)/utils
VPATH:= $(VPATH):$(utilsdir): \
    $(utilsdir)/error:$(utilsdir)/init: \
    $(utilsdir)/cache

SUBSRCS=
include $(utilsdir)/error/Makefile.inc
include $(utilsdir)/init/Makefile.inc
include $(utilsdir)/cache/Makefile.inc
SRCS_UTILS:= $(SUBSRCS)

HEADERS+=elog.h