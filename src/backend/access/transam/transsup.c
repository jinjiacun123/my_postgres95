#include "utils/nabstime.h"
#include "utils/rel.h"
#include "utils/elog.h"
#include "utils/bit.h"
#include "storage/buf.h"
#include "storage/bufmgr.h"
#include "access/transam.h"

AbsoluteTime
TransBlockNumberGetCommitTime(Relation      relation,
                              BlockNumber   blockNumber,
                              TransactionId xid,
                              bool          *failP){
  Buffer       buffer;
  Block        block;
  bool         localfail;
  AbsoluteTime xtime;

  RelationSetLockForRead(relation);
  buffer = ReadBuffer(relation, blockNumber);
  block  = BufferGetBlock(buffer);

  if(failP == NULL)
    failP = &localfail;
  (*failP) = false;

  xtime = TransBlockGetCommitTime(block, xid);

  ReleaseBuffer(buffer);

  RelationUnsetLockForRead(relation);

  if((*failP) == false)
    return xtime;
  else
    return INVALID_ABSTIME;
}

void
TransComputeBlockNumber(Relation       relation,
                        TransactionId  transactionId,
                        BlockNumber    *blockNumberOutP){
  long  itemsPerBlock;
  if(relation == LogRelation)
    itemsPerBlock = TP_NumXidStatusPerBlock;
  else if(relation == TimeRelation)
    itemsPerBlock = TP_NumTimePerBlock;
  else
    elog(WARN, "TransComputeBlockNumber: unknown relation");

  (*blockNumberOutP) = transactionId;
}

XidStatus
TransBlockNumberGetXidStatus(Relation      relation,
                             BlockNumber   blockNumber,
                             TransactionId xid,
                             bool          *failP){
  Buffer        buffer;
  Block         block;
  XidStatus     xstatus;
  bool          localfail;

  RelationSetLockForRead(relation);

  buffer = ReadBuffer(relation, blockNumber);
  block  = BufferGetBlock(buffer);

  if(failP == NULL)
    failP = &localfail;
  (*failP) = false;

  xstatus = TransBlockGetXidStatus(block, xid);

  ReleaseBuffer(buffer);

  RelationUnsetLockForRead(relation);

  return xstatus;
}

AbsoluteTime
TransBlockGetCommitTime(Block         tblock,
                        TransactionId transactionId){
  Index        index;
  AbsoluteTime *timeArray;

  if(tblock == NULL)
    return INVALID_ABSTIME;

  index = transactionId % TP_NumTimePerBlock;
  timeArray = (AbsoluteTime *)tblock;

  return (AbsoluteTime)timeArray[index];
}

XidStatus
TransBlockGetXidStatus(Block         tblock,
                       TransactionId transactionId){
  Index          index;
  bits8          bit1;
  bits8          bit2;
  BitIndex       offset;

  if(tblock == NULL){
    return XID_INVALID;
  }

  index = transactionId % TP_NumXidStatusPerBlock;

  offset = BitIndexOf(index);
  bit1   = ((bits8) BitArrayBitIsSet((BitArray)tblock, offset++)) << 1;
  bit2   = (bits8)  BitArrayBitIsSet((BitArray)tblock, offset);

  return (XidStatus)(bit1 | bit2);
}
