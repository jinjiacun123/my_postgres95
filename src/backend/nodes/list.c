#include "postgres.h"
#include "nodes/pg_list.h"

List*
lcons(void *datum, List *list){
  List *l = makeNode(List);
  lfirst(l) = datum;
  lnext(l)  = list;
  return l;
}
