#ifndef HTOP_H
#define HTOP_H
#include "storage/itemptr.h"
#include "utils/nabstime.h"

#define MinHeapTupleBitmapSize 32

typedef struct HeapTupleData {
  unsigned int    t_len;
  ItemPointerData t_ctid;
  ItemPointerData t_chain;

  Oid             t_oid;

  CommandId       t_cmin;
  CommandId       t_cmax;

  TransactionId   t_xmin;
  TransactionId   t_xmax;

  AbsoluteTime    t_tmin;
  AbsoluteTime    t_tmax;

  int16           t_natts;
  char            t_vtype;

  char            t_infomask;

  uint8           t_hoff;
  bits8           t_bits[MinHeapTupleBitmapSize/8];
} HeapTupleData;

typedef HeapTupleData *HeapTuple;
#endif
