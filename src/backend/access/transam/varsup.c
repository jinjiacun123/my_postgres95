#include "postgres.h"
#include "storage/buf.h"
#include "utils/rel.h"
#include "access/transam.h"
#include "catalog/catname.h"
#include "utils/elog.h"

static int prefetched_oid_count = 0;
static Oid next_prefetched_oid;
#define VAR_OID_PREFETCH 32
int OidGenLockId;

void
GetNewTransactionId(TransactionId *xid)
{
  TransactionId nextid;

  if(AMI_OVERRIDE){
    TransactionIdStore(AmiTransactionId, xid);
    return;
  }
}

void
GetNewObjectId(Oid *oid_return){
  if(prefetched_oid_count == 0){
    int oid_block_size = VAR_OID_PREFETCH;
    if(! RelationIsValid(VariableRelation))
      VariableRelation = heap_openr(VariableRelationName);
    GetNewObjectIdBlock(&next_prefetched_oid, oid_block_size);
    prefetched_oid_count = oid_block_size;
  }

  if(PointerIsValid(oid_return))
    (*oid_return) = next_prefetched_oid;

  next_prefetched_oid++;
  prefetched_oid_count--;
}

void
GetNewObjectIdBlock(Oid *oid_return,
                    int oid_block_size){
  Oid nextoid;

  SpinAcquire(OidGenLockId);
  VariableRelationGetNextOid(&nextoid);
  if(PointerIsValid(oid_return))
    (*oid_return) = nextoid;
  nextoid += oid_block_size;
  VariableRelationPutNextOid(&nextoid);
  SpinRelease(OidGenLockId);
}

void
VariableRelationGetNextOid(Oid *oid_return){
  Buffer                   buf;
  VariableRelationContents var;

  if(! RelationIsValid(VariableRelation)) {
    if(PointerIsValid(oid_return))
      (*oid_return) = InvalidOid;
    return;
  }
  buf = ReadBuffer(VariableRelation, 0);
  if(! BufferIsValid(buf)){
    SpinRelease(OidGenLockId);
    elog(WARN, "VariableRelationGenNextid: ReadBuffer failed");
  }
  var = (VariableRelationContents) BufferGetBlock(buf);
  if(PointerIsValid(oid_return)){
    if(OidIsValid(var->nextOid))
      (*oid_return) = var->nextOid;
    else
      (*oid_return) = BootstrapObjectIdData;
  }

  ReleaseBuffer(buf);
}

void
VariableRelationPutNextOid(Oid *oidP){
  Buffer buf;
  VariableRelationContents var;

  if(! RelationIsValid(VariableRelation))
    return;

  if(! PointerIsValid(oidP)){
    SpinRelease(OidGenLockId);
    elog(WARN, "VariableRelationPutNextOid: invalid oid pointer");
  }

  buf = ReadBuffer(VariableRelation, 0);
  if(! BufferIsValid(buf)){
    SpinRelease(OidGenLockId);
    elog(WARN, "VariableRelationPutNextid: ReadBuffer failed");
  }

  var = (VariableRelationContents) BufferGetBlock(buf);
  var->nextOid = (*oidP);
  WriteBuffer(buf);
}
