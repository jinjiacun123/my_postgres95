stordir=$(CURDIR)/storage
VPATH:=$(VPATH):$(stordir):$(stordir)/ipc

SUBSRCS=
include $(stordir)/ipc/Makefile.inc


SRCS_STORAGE:= $(SUBSRCS)

HEADERS+=backend.h sinval.h sinvaladt.h lmgr.h