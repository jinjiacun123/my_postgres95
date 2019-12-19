portdir = $(CURDIR)/port/$(PORTNAME)
VPATH:= $(VPATH):$(portdir)

SUBSRCS=
include $(portdir)/Makefile.inc
SRCS_PORT:= $(SUBSRCS)