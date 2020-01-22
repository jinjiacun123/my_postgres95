stordir=$(CURDIR)/storage
VPATH:=$(VPATH):$(stordir):$(stordir)/buffer:$(stordir)/ipc:\
       $(stordir)/lmgr:$(stordir)/smgr:$(stordir)/page:\
       $(stordir)/file

SUBSRCS=
include $(stordir)/buffer/Makefile.inc
include $(stordir)/ipc/Makefile.inc
include $(stordir)/lmgr/Makefile.inc
include $(stordir)/smgr/Makefile.inc
include $(stordir)/page/Makefile.inc
include $(stordir)/file/Makefile.inc


SRCS_STORAGE:= $(SUBSRCS)

HEADERS+=backend.h sinval.h sinvaladt.h lmgr.h buf.h bufmgr.h buf_internals.h shmem.h smgr.h itemid.h itemptr.h item.h fd.h