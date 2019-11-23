accdir=$(CURDIR)/access
VPATH:=$(VPATH):$(accdir):\
        $(accdir)/transam

SUBSRCS=
include $(accdir)/transam/Makefile.inc

SRCS_ACCESS:=$(SUBSRCS)

HEADERS+= xact.h