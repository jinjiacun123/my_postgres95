#ifndef OFF_H
#define OFF_H
#include "storage/itemid.h"

#define BLCKSZ 8192

typedef uint16 OffsetNumber;

#define InvalidOffsetNumber ((OffsetNumber)0)
#define FirstOffsetNumber   ((OffsetNumber) 1)
#define MaxOffsetNumber     ((OffsetNumber)(BLCKSZ /sizeof(ItemIdData)))

#define OffsetNumberNext(offsetNumber) \
  ((OffsetNumber)(1 + (offsetNumber)))
#define OffsetNumberPrev(offsetNumber) \
  ((OffsetNumber) ( -1 + (offsetNumber)))


#endif
