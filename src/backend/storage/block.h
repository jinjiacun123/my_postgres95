#ifndef BLOCK_H
#define BLOCK_H
#include "c.h"

typedef uint32 BlockNumber;

#define InvalidBlockNumber (BlockNumber) 0xFFFFFFFF

typedef struct BlockIdData{
  uint16 bi_hi;
  uint16 bi_lo;
} BlockIdData;

#endif
