catdir=$(CURDIR)/catalog
VPATH:=$(VPATH):$(catdir)

SRCS_CATALOG=pg_proc.c heap.c catalog.c index.c

HEADERS+= pg_attribute.h pg_proc.h pg_type.h pg_am.h pg_rewrite.h