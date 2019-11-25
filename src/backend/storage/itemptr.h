#ifndef ITEMPTR_H
#define ITEMPTR_H
#include "storage/block.h"
#include "storage/off.h"

typedef struct ItemPointerData{
  BlockIdData  ip_blkid;
  OffsetNumber ip_posid;
} ItemPointerData;

typedef ItemPointerData *ItemPointer;

#endif
