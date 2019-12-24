#include "postgres.h"
#include "access/xact.h"
#include "storage/lmgr.h"
#include "utils/rel.h"
#include "catalog/catname.h"

#define LOCKDEBUGALL_30

void
RelationSetLockForDescriptorOpen(Relation relation){
  Assert(RelationIsValid(relation));
  if(LockingDisabled())
    return;

  LOCKDEBUGALL_30;
}

void
RelationInitLockInfo(Relation relation){
  LockInfo            info;
  char                *relname;
  Oid                 relationid;
  bool                processingVariable;
  extern Oid          MyDatabaseId;
  extern GlobalMemory CacheCxt;

  Assert(RelationIsValid(relation));
  Assert(OidIsValid(RelationGetRelationId(relation)));

  info               = (LockInfo) relation->lockInfo;
  relname            = (char *)RelationGetRelationName(relation);
  relationid         = RelationGetRelationId(relation);
  processingVariable = (strcmp(relname, VariableRelationName) == 0);

  if(! PointerIsValid(info)){
    MemoryContext oldcxt;

    oldcxt = MemoryContextSwitchTo((MemoryContext)CacheCxt);
    info   = (LockInfo)palloc(sizeof(LockInfoData));
    MemoryContextSwitchTo(oldcxt);
  } else if(processingVariable){
    if(IsTransactionState()){
      TransactionIdStore(GetCurrentTransactionId(), &info->transactionIdData);
    }
    info->flags = 0x0;
    return;
  } else if(info->initialized){
    return;
  }

  if(IsSharedSystemRelationName(relname))
    LRelIdAssign(&info->lRelId, InvalidOid, relationid);
  else
    LRelIdAssign(&info->lRelId, MyDatabaseId, relationid);

  if(processingVariable)
    TransactionIdStore(GetCurrentTransactionId(), &info->transactionIdData);
  else if(IsTransactionState())
    TransactionIdStore(GetCurrentTransactionId(), &info->transactionIdData);
  else
    StoreInvalidTransactionId(&(info->transactionIdData));

  info->flags        = 0x0;
  info->initialized  = (bool)true;
  relation->lockInfo = (Pointer)info;
 }
