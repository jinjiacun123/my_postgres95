accdir=$(CURDIR)/access
VPATH:=$(VPATH):$(accdir):\
        $(accdir)/common:$(accdir)/transam

SUBSRCS=
include $(accdir)/common/Makefile.inc
include $(accdir)/transam/Makefile.inc

SRCS_ACCESS:=$(SUBSRCS)

HEADERS+= xact.h tupdesc.h