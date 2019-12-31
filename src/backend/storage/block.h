#ifndef BLOCK_H
#define BLOCK_H
#include "c.h"

typedef uint32 BlockNumber;

#define InvalidBlockNumber (BlockNumber) 0xFFFFFFFF

#define BlockIdGetBlockNumber(blockId)\
  (AssertMacro(BlockIdIsValid(blockId))? \
  (BlockNumber) (((blockId)->bi_hi << 16) | ((uint16)(blockId)->bi_lo)):\
   (BlockNumber) InvalidBlockNumber)

typedef struct BlockIdData{
  uint16 bi_hi;
  uint16 bi_lo;
} BlockIdData;

#endif
