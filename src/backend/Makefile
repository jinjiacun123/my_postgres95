BIGOBJS=true
PROG=postgres

MKDIR=../mk
include $(MKDIR)/postgres.mk

include $(CURDIR)/access/Makefile.inc
include $(CURDIR)/bootstrap/Makefile.inc
include $(CURDIR)/catalog/Makefile.inc
include $(CURDIR)/lib/Makefile.inc
include $(CURDIR)/main/Makefile.inc
include $(CURDIR)/nodes/Makefile.inc
include $(CURDIR)/parser/Makefile.inc
#include $(CURDIR)/port/Makefile.inc
include $(CURDIR)/rewrite/Makefile.inc
include $(CURDIR)/storage/Makefile.inc
include $(CURDIR)/utils/Makefile.inc

SRCS:=${SRCS_ACCESS} ${SRCS_BOOTSTRAP} ${SRCS_CATALOG} ${SRCS_LIB} \
      ${SRCS_MAIN} ${SRCS_REWRITE} ${SRCS_PARSER} ${SRCS_REWRITE} \
      ${SRCS_STORAGE} ${SRCS_UTILS}

ifeq ($(BIGOBJS), true)
OBJS= ACCESS.o BOOTSTRAP.o CATALOG.o MAIN.o NODES.o PARSER.o STORAGE.o UTILS.o
CLEANFILES += $(subst .s,.o,$(SRCS:.c=.o)) $(OBJS)
endif

postgres:$(POSTGRES_DEPEND) $(OBJS) $(EXPORTS)
	$(CC) $(LDFLAGS) -o $(objdir)/$(@F) $(addprefix $(objdir)/, $(notdir $(OBJS))) $(LDADD)

CFLAGS += -DPOSTGRESDIR='"$(POSTGRESDIR)"' \
	-DPGDATADIR='"$(DATADIR)"' \
	-I$(CURDIR)/. -I$(CURDIR)/$(objdir) \
	-I$(CURDIR)/include \
	-I$(CURDIR)/port/$(PORTNAME)

ifeq ($(BIGOBJS), true)
OBJS_ACCESS:= $(SRCS_ACCESS:%.c=$(objdir)/%.o)
OBJS_BOOTSTRAP:= $(SRCS_BOOTSTRAP:%.c=$(objdir)/%.o)
OBJS_CATALOG:=$(SRCS_CATALOG:%.c=$(objdir)/%.o)
#OBJS_LIB:=$(SRCS_LIB:%.c=$(objdir)/%.o)
OBJS_MAIN:=$(SRCS_MAIN:%.c=$(objdir)/%.o)
OBJS_NODES:=$(SRCS_NODES:%.c=$(objdir)/%.o)
OBJS_PARSER:=$(SRCS_PARSER:%.c=$(objdir)/%.o)
#OBJS REWRITE:=$(SRCS_REWRITE:%.c=$(objdir)/%.o)
OBJS_STORAGE:=$(SRCS_STORAGE:%.c=$(objdir)/%.o)
OBJS_UTILS:=$(SRCS_UTILS:%.c=$(objdir)/%.o)

ACCESS.o:$(OBJS_ACCESS)
	$(make_partial)
BOOTSTRAP.o:$(OBJS_BOOTSTRAP)
	$(make_partial)
CATALOG.o:$(OBJS_CATALOG)
	$(make_partial)
#LIB.o:$(OBJS_LIB)
#	$(make_partial)
MAIN.o:$(OBJS_MAIN)
	$(make_partial)
NODES.o:$(OBJS_NODES)
	$(make_partial)
PARSER.o:$(OBJS_PARSER)
	$(make_partial)
#REWRITE.o:$(OBJS_REWRITE)
#	$(make_partial)
STORAGE.o:$(OBJS_STORAGE)
	$(make_partial)
UTILS.o:$(OBJS_UTILS)
	$(make_partial)
endif
