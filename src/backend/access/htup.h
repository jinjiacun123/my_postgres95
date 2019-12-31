#ifndef HTOP_H
#define HTOP_H
#include "storage/itemptr.h"
#include "utils/nabstime.h"

#define ObjectIdAttributeNumber  (-2)

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

#define GETSTRUCT(TUP) (((char*)(TUP)) + ((HeapTuple)(TUP))->t_hoff)

#define HeapTupleIsValid(tuple) PointerIsValid(tuple)

#define SelfItemPointerAttributeNumber     (-1)
#define ObjectIdAttributeNumber            (-2)
#define MinTransactionIdAttributeNumber    (-3)
#define MinCommandIdAttributeNumber        (-4)
#define MaxTransactionIdAttributeNumber    (-5)
#define MaxCommandIdAttributeNumber        (-6)
#define ChainItemPointerAttributeNumber    (-7)
#define AnchorItemPointerAttributeNumber   (-8)
#define MinAbsoluteTimeAttributeNumber     (-9)
#define MaxAbsoluteTimeAttributeNumber     (-10)
#define VersionTypeAttributeNumber         (-11)
#define FirstLowInvalidHeapAttributeNumber (-12)

#define HEAP_HASNULL            0x01
#define HEAP_HASVARLENA         0x02

#define HeapTupleNoNulls(tuple)\
  (!(((HeapTuple)(tuple))->t_infomask & HEAP_HASNULL))

#define HeapTupleAllFixed(tuple)\
  (!(((HeapTuple) (tuple))->t_infomask & HEAP_HASVARLENA ))

#endif
