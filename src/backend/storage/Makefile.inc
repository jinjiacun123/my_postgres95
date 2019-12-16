stordir=$(CURDIR)/storage
VPATH:=$(VPATH):$(stordir):$(stordir)/buffer:$(stordir)/ipc

SUBSRCS=
include $(stordir)/buffer/Makefile.inc
include $(stordir)/ipc/Makefile.inc


SRCS_STORAGE:= $(SUBSRCS)

HEADERS+=backend.h sinval.h sinvaladt.h lmgr.h buf.h bufmgr.h buf_internals.h shmem.h