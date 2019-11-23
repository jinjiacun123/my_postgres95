#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H
#include "utils/elog.h"

typedef struct hashnode{
  int strnum;
  struct hashnode *next;
} hashnode;

extern hashnode    *FindStr(char *str, int length, hashnode *mderef);
extern int         CompHash(char *str, int len);
extern hashnode    *AddStr(char *str, int strlength, int mderef);
#endif
