#ifndef TUPTABLE_H
#define TUPTABLE_H
#include "nodes/nodes.h"
#include "access/htup.h"
#include "access/tupdesc.h"
#include "storage/buf.h"

typedef struct TupleTableSlot {
  NodeTag    type;
  HeapTuple  val;
  bool       ttc_shouldFree;
  bool       ttc_descIsNew;
  TupleDesc  ttc_tupleDescriptor;
  Buffer     ttc_buffer;
  int        ttc_whichplan;
} TupleTableSlot;

typedef struct TupleTableData {
  int            size;
  int            next;
  TupleTableSlot *array;
} TupleTableData;

typedef TupleTableData *TupleTable;



#endif
