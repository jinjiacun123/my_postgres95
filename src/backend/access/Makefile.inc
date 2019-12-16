accdir=$(CURDIR)/access
VPATH:=$(VPATH):$(accdir):\
        $(accdir)/common:$(accdir)/heap:$(accdir)/transam

SUBSRCS=
include $(accdir)/common/Makefile.inc
include $(accdir)/heap/Makefile.inc
include $(accdir)/transam/Makefile.inc

SRCS_ACCESS:=$(SUBSRCS)

HEADERS+= xact.h tupdesc.h transam.h heapam.h