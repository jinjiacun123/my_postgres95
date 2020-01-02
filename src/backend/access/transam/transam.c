#include "postgres.h"
#include "utils/rel.h"
#include "utils/elog.h"
#include "access/transam.h"

TransactionId NullTransactionId = (TransactionId) 0;
TransactionId AmiTransactionId  = (TransactionId)512;

Relation LogRelation      = (Relation)NULL;
Relation TimeRelation     = (Relation)NULL;
Relation VariableRelation = (Relation)NULL;

TransactionId     cachedGetCommitTimeXid;
AbsoluteTime      cachedGetCommitTime;
TransactionId     cachedTestXid;
XidStatus         cachedTestXidStatus;

bool
TransactionIdDidCommit(TransactionId transactionId){
  if(AMI_OVERRIDE)
    return true;

  return TransactionLogTest(transactionId, XID_COMMIT);
}

AbsoluteTime
TransactionIdGetCommitTime(TransactionId transactionId){
  BlockNumber    blockNumber;
  AbsoluteTime   commitTime;
  bool           fail = false;

  if(! RelationIsValid(TimeRelation))
    return INVALID_ABSTIME;

  if(TransactionIdEquals(transactionId, cachedGetCommitTimeXid))
    return cachedGetCommitTime;

  TransComputeBlockNumber(TimeRelation, transactionId, &blockNumber);
  commitTime = TransBlockNumberGetCommitTime(TimeRelation,
                                             blockNumber,
                                             transactionId,
                                             &fail);
  if(! fail){
    TransactionIdStore(transactionId, &cachedGetCommitTimeXid);
    cachedGetCommitTime = commitTime;
    return commitTime;
  } else
    return INVALID_ABSTIME;
}

bool
TransactionLogTest(TransactionId transactionId,
                   XidStatus     status){
  BlockNumber     blockNumber;
  XidStatus       xidstatus;
  bool            fail = false;

  if(! RelationIsValid(LogRelation))
    return (bool)(status == XID_COMMIT);

  if(TransactionIdEquals(transactionId, cachedTestXid))
    return (bool)(status == cachedTestXidStatus);

  TransComputeBlockNumber(LogRelation, transactionId, &blockNumber);
  xidstatus = TransBlockNumberGetXidStatus(LogRelation,
                                           blockNumber,
                                           transactionId,
                                           &fail);
  if(!fail){
    TransactionIdStore(transactionId, &cachedTestXid);
    cachedTestXidStatus = xidstatus;
    return (bool)(status == xidstatus);
  }

  elog(WARN, "TransactionLogTest: failed to get xidstatus");
  return(false);
}
