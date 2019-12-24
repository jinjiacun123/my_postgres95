#ifndef PG_LIST_H
#define PG_LIST_H

#include "nodes/nodes.h"

typedef struct List {
  NodeTag     type;
  void        *elem;
  struct List *next;
} List;

#define lfirst(l) ((l)->elem)
#define lnext(l)  ((l)->next)

typedef struct Value {
  NodeTag type;
  union ValueUnion {
    char   *str;
    long   ival;
    double dval;
  } val;
} Value;

extern Value *makeString(char *str);
extern Value *makeFloat(double d);
extern Value *makeInteger(long i);

#endif
