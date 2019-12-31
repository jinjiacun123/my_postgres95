accdir=$(CURDIR)/access
VPATH:=$(VPATH):$(accdir):\
        $(accdir)/common:$(accdir)/heap:$(accdir)/transam:\
        $(accdir)/index

SUBSRCS=
include $(accdir)/common/Makefile.inc
include $(accdir)/heap/Makefile.inc
include $(accdir)/transam/Makefile.inc
include $(accdir)/index/Makefile.inc

SRCS_ACCESS:=$(SUBSRCS)

HEADERS+= xact.h tupdesc.h transam.h heapam.h strat.h valid.h