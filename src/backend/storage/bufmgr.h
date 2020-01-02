#ifndef BUFMGR_H
#define BUFMGR_H
#include "c.h"
#include "machine.h"
#include "storage/buf_internals.h"
#include "storage/block.h"
#include "storage/off.h"

#define P_NEW InvalidBlockNumber

#define BufferDescriptorGetBuffer(bdesc) ((bdesc)->buf_id +1)

#define ItemPointerSetInvalid(pointer) \
  Assert(PointerIsValid(pointer)); \
  BlockIdSet(&((pointer)->ip_blkid), InvalidBlockNumber); \
  (pointer)->ip_posid = InvalidOffsetNumber;


typedef void *Block;
extern bool        BufferIsValid(Buffer bufnum);
extern int         WriteBuffer(Buffer buffer);
extern void        IncrBufferRefCount(Buffer buffer);
extern BlockNumber RelationGetNumberOfBlocks(Relation relation);
extern Buffer      RelationGetBufferWithBuffer(Relation    relation,
                                               BlockNumber blockNumber,
                                               Buffer      buffer);
extern Buffer      ReleaseAndReadBuffer(Buffer      buffer,
                                        Relation    relation,
                                        BlockNumber blockNum);
#endif
