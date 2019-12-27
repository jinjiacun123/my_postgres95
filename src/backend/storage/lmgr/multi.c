#include "postgres.h"
#include "storage/lmgr.h"
#include "storage/lock.h"
#include "storage/multilev.h"

LockTableId  MultiTableId = (LockTableId)NULL;

bool
MultiReleaseReln(LockInfo linfo,
                 LOCKT    lockt){
  LOCKTAG tag;

  memset(&tag, 0, sizeof(LOCKTAG));
  tag.relId = linfo->lRelId.relId;
  tag.dbId  = linfo->lRelId.dbId;

  return (MultiRelease(MultiTableId,
                      &tag,
                      lockt,
                      RELN_LEVEL));
}

bool
MultiLockReln(LockInfo linfo,
              LOCKT    lockt){

  LOCKTAG   tag;

  memset(&tag, 0, sizeof(tag));
  tag.relId = linfo->lRelId.relId;
  tag.dbId  = linfo->lRelId.dbId;
  return(MultiAcquire(MultiTableId,
                      &tag,
                      lockt,
                      RELN_LEVEL));
}
