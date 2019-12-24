#ifndef TUPDESC_H
#define TUPDESC_H
#include "nodes/pg_list.h"
#include "catalog/pg_attribute.h"
typedef struct tupleDesc {
  int                natts;
  AttributeTupleForm *attrs;
} *TupleDesc;

extern TupleDesc CreateTemplateTupleDesc(int natts);
extern TupleDesc CreateTupleDesc(int natts, AttributeTupleForm *attrs);
extern TupleDesc CreateTupleDescCopy(TupleDesc tupdesc);
#endif
