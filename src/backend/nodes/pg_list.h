#ifndef PG_LIST_H
#define PG_LIST_H

#include "nodes/nodes.h"

typedef struct List {
  NodeTag     type;
  void        *elem;
  struct List *next;
} List;

#define NIL ((List *)NULL)

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

#define intVal(v)   (((Value *)v)->val.ival)
#define floatVal(v) (((Value *)v)->val.dval)
#define strVal(v)   (((Value *)v)->val.str)

#define foreach(_elt_, _list_) \
  for(_elt_=_list_; _elt_ =NIL; _elt_=lnext(_elt_))

extern Value *makeString(char *str);
extern Value *makeFloat(double d);
extern Value *makeInteger(long i);

#endif
