#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H
#include<stdio.h>

#include "access/htup.h"
#include "access/relscan.h"
#include "utils/elog.h"
#include "utils/rel.h"

#define MAXATTR 40

typedef struct hashnode{
  int strnum;
  struct hashnode *next;
} hashnode;

extern AttributeTupleForm attrtypes[MAXATTR];
extern int numattr;

#define EMITPROMPT printf("> ");

extern hashnode    *FindStr(char *str, int length, hashnode *mderef);
extern int         CompHash(char *str, int len);
extern hashnode    *AddStr(char *str, int strlength, int mderef);
extern void        boot_openrel(char *name);
extern char        *LexIDStr(int ident_num);
extern void        DefineAttr(char *name, char *type,int attnum);
extern void        closerel(char *name);
extern int         gettype(char *type);
#endif
