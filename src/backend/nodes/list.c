#include "postgres.h"
#include "nodes/pg_list.h"

List*
lcons(void *datum, List *list){
  List *l = makeNode(List);
  lfirst(l) = datum;
  lnext(l)  = list;
  return l;
}

Value *
makeString(char *str){
  Value *v   = makeNode(Value);
  v->type    = T_String;
  v->val.str = str;
  return v;
}

Value *
makeInteger(long i){
  Value *v    = makeNode(Value);
  v->type     = T_Integer;
  v->val.ival = i;
  return v;
}

Value *
makeFloat(double d){
  Value *v    = makeNode(Value);
  v->type     = T_Float;
  v->val.dval = d;
  return v;
}
