#BIGOBJS = false

ifdef LINUX_ELF
CC=gcc
#LDADD+= -ldl
#CFLAGS+= -DLINUX_ELF

else
LDADD+= -ldld
SUBSRCS+= dynloader.c
endif

HEADERS+= machine.h
CFLAGS+= -DNEED_CBRT