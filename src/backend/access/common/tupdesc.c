#include "postgres.h"
#include "access/tupdesc.h"

TupleDesc
CreateTupleDesc(int natts, AttributeTupleForm *attrs){
  TupleDesc desc;

 AssertArg(natts >= 1);

  desc        = (TupleDesc) palloc(sizeof(struct tupleDesc));
  desc->attrs = attrs;
  desc->natts = natts;

  return (desc);
}

TupleDesc
CreateTupleDescCopy(TupleDesc tupdesc){
  TupleDesc desc;
  int i, size;

  desc        = (TupleDesc)palloc(sizeof(struct tupleDesc));
  desc->natts = tupdesc->natts;
  size        = desc->natts * sizeof(AttributeTupleForm);
  desc->attrs = (AttributeTupleForm*)palloc(size);
  for(i = 0; i < desc->natts; i++){
    desc->attrs[i] = (AttributeTupleForm)palloc(ATTRIBUTE_TUPLE_SIZE);
    memmove(desc->attrs[i], tupdesc->attrs[i], ATTRIBUTE_TUPLE_SIZE);
  }

  return desc;
}

TupleDesc
CreateTemplateTupleDesc(int natts){
  uint32    size;
  TupleDesc desc;

  AssertArg(natts >= 1);

  size = natts * sizeof(AttributeTupleForm);
  desc = (TupleDesc) palloc(sizeof(struct tupleDesc));
  desc->attrs = (AttributeTupleForm*) palloc(size);
  memset(desc->attrs, 0, size);

  desc->natts = natts;

  return (desc);
}
