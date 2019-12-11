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
