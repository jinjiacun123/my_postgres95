#include "postgres.h"
#include "utils/rel.h"
#include "access/transam.h"

TransactionId NullTransactionId = (TransactionId) 0;
TransactionId AmiTransactionId  = (TransactionId)512;

Relation TimeRelation     = (Relation)NULL;
Relation VariableRelation = (Relation)NULL;

TransactionId     cachedGetCommitTimeXid;
AbsoluteTime      cachedGetCommitTime;

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
