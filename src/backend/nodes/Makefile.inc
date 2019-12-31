VPATH:=$(VPATH):$(CURDIR)/nodes

SRCS_NODES= nodes.c list.c read.c readfuncs.c

HEADERS+=memnodes.h nodes.h pg_list.h readfuncs.h relation.h primnodes.h plannodes.h