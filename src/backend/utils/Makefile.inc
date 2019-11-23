utilsdir=$(CURDIR)/utils
VPATH:= $(VPATH):$(utilsdir):\
        $(utilsdir)/error

SUBSRCS=
include $(utilsdir)/error/Makefile.inc
SRCS_UTILS:= $(SUBSRCS)

HEADERS+=elog.h