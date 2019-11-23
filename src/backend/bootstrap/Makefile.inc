bootdir=$(CURDIR)/bootstrap
VPATH:=$(VPATH):$(bootdir)

BOOTYACCS=bootparse.c

SRCS_BOOTSTRAP= bootparse.c bootscanner.c bootstrap.c

$(BOOTYACCS):bootparse.y
	cd $(objdir); \
    $(YACC) $(YFLAGS) $<; \
    sed -f $(bootdir)/boot.sed < y.tab.c > bootparse.c; \
    mv y.tab.h bootstrap_token.h; \
    rm -f y.tab.c

$(objdir)/bootparse.o:bootparse.c
	$(cc_inobjdir)

bootscanner.c:bootscanner.l
	cd $(objdir); \
    $(LEX) $<; \
    sed -f $(bootdir)/boot.sed < lex.yy.c > bootscanner.c; \
    rm lex.yy.c

$(objdir)/bootscanner.o:bootscanner.c
	$(cc_inobjdir)

POSTGRES_DEPEND+= $(BOOTYACCS) bootscanner.c

CLEANFILES+= bootscanner.c $(BOOTYACC) y.tab.h y.output

HEADERS+= bootstrap.h

bootstrap.o:$(BOOTYACCS)
