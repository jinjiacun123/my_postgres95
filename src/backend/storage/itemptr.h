#ifndef ITEMPTR_H
#define ITEMPTR_H
#include "storage/block.h"
#include "storage/off.h"

typedef struct ItemPointerData{
  BlockIdData  ip_blkid;
  OffsetNumber ip_posid;
} ItemPointerData;

typedef ItemPointerData *ItemPointer;

#define ItemPointerIsValid(pointer) \
  ((bool) (PointerIsValid(pointer) && ((pointer)->ip_posid != 0)))

#define ItemPointerGetBlockNumber(pointer) \
  (AssertMacro(ItemPointerIsValid(pointer)) ?                       \
   BlockIdGetBlockNumber(&(pointer)->ip_blkid) : (BlockNumber) 0)

#define ItemPointerSetBlockNumber(pointer, blockNumber)\
  Assert(PointerIsValid(pointer));\
  BlockIdSet(&((pointer)->ip_blkid), blockNumber)

#define ItemPointerGetOffsetNumber(pointer) \
  (AssertMacro(ItemPointerIsValid(pointer))?      \
  (pointer)->ip_posid:\
   InvalidOffsetNumber)


#endif
