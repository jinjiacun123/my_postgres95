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

#endif
