#ifndef TUPDESC_H
#define TUPDESC_H
#include "catalog/pg_attribute.h"
typedef struct tupledesc {
  int                natts;
  AttributeTupleForm *attrs;
} *TupleDesc;
#endif
