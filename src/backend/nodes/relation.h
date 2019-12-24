#ifndef RELATION_H
#define RELATION_H

typedef struct Iter{
  NodeTag type;
  Node    *iterexpr;
  Oid     itertype;
} Iter;


#endif
