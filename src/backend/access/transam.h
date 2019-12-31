#ifndef TRANSAM_H
#define TRANSAM_H
#include "utils/nabstime.h"

#define XID_COMMIT      2
#define XID_ABORT       1
#define XID_INPROGRESS  0
#define XID_INVALID     3

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
extern Relation VariableRelation;

extern void         GetNewObjectIdBlock(Oid *oid_return, int oid_block_size);
extern void         VariableRelationGetNextOid(Oid *oid_return);
extern void         VariableRelationPutNextOid(Oid *oidP);
extern bool         TransactionIdDidCommit(TransactionId transactionId);
extern AbsoluteTime TransactionIdGetCommitTime(TransactionId transactionId);
#endif
