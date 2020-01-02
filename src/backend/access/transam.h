#ifndef TRANSAM_H
#define TRANSAM_H
#include "utils/nabstime.h"
#include "storage/bufmgr.h"

#define XID_COMMIT      2
#define XID_ABORT       1
#define XID_INPROGRESS  0
#define XID_INVALID     3

#define BitIndexOf(N)  ((N) *2)

#define TP_DataSize             BLCKSZ
#define TP_NumXidStatusPerBlock (TP_DataSize * 4)
#define TP_NumTimePerBlock      (TP_DataSize / 4)

typedef unsigned char XidStatus;

#define BootstrapObjectIdData 16384
typedef struct VariableRelationContentsData {
  int           TransSystemVersion;
  TransactionId nextXidData;
  TransactionId lastXidData;
  Oid           nextOid;
} VariableRelationContentsData;

typedef VariableRelationContentsData * VariableRelationContents;

extern bool AMI_OVERRIDE;
extern TransactionId NullTransactionId;
extern TransactionId AmiTransactionId;
extern Relation      VariableRelation;
extern Relation      TimeRelation;
extern Relation      LogRelation;

extern void         GetNewObjectIdBlock(Oid *oid_return, int oid_block_size);
extern void         VariableRelationGetNextOid(Oid *oid_return);
extern void         VariableRelationPutNextOid(Oid *oidP);
extern bool         TransactionIdDidCommit(TransactionId transactionId);
extern AbsoluteTime TransactionIdGetCommitTime(TransactionId transactionId);
extern bool         TransactionLogTest(TransactionId   transactionId,
                                       XidStatus       status);
extern AbsoluteTime TransBlockNumberGetCommitTime(Relation      relation,
                                                  BlockNumber   blockNumber,
                                                  TransactionId xid,
                                                  bool          *failP);
extern void         TransComputeBlockNumber(Relation      relation,
                                            TransactionId transactionId,
                                            BlockNumber   *blockNumberOutP);
extern XidStatus    TransBlockNumberGetXidStatus(Relation      relation,
                                                 BlockNumber   blockNumber,
                                                 TransactionId xid,
                                                 bool          *failP);
extern AbsoluteTime TransBlockGetCommitTime(Block         tblock,
                                            TransactionId transactionId);
extern XidStatus    TransBlockGetXidStatus(Block         tblock,
                                           TransactionId transactionId);
#endif
