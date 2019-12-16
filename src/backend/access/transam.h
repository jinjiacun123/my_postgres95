#ifndef TRANSAM_H
#define TRANSAM_H

#define BootstrapObjectIdData 16384
typedef struct VariableRelationContentsData {
  int           TransSystemVersion;
  TransactionId nextXidData;
  TransactionId lastXidData;
  Oid           nextOid;
} VariableRelationContentsData;

typedef VariableRelationContentsData * VariableRelationContents;

extern bool AMI_OVERRIDE;
extern TransactionId AmiTransactionId;
extern Relation VariableRelation;

extern void GetNewObjectIdBlock(Oid *oid_return, int oid_block_size);
extern void VariableRelationGetNextOid(Oid *oid_return);
extern void VariableRelationPutNextOid(Oid *oidP);
#endif
