#ifndef TUPDESC_H
#define TUPDESC_H
#include "catalog/pg_attribute.h"
typedef struct tupleDesc {
  int                natts;
  AttributeTupleForm *attrs;
} *TupleDesc;

extern TupleDesc CreateTupleDesc(int natts, AttributeTupleForm *attrs);
#endif
