#ifndef LMGR_H
#define LMGR_H
#include "postgres.h"
#include "storage/itemptr.h"
#include "nodes/memnodes.h"
#include "utils/rel.h"

typedef struct LRelId {
  Oid relId;
  Oid dbId;
} LRelId;

typedef struct LockInfoData {
  bool          initialized;
  LRelId        lRelId;
  TransactionId transactionIdData;
  uint16        flags;
} LockInfoData;
typedef LockInfoData *LockInfo;

#define LockInfoIsValid(linfo) \
  ((PointerIsValid(linfo)) && ((LockInfo)linfo)->initialized)

extern LRelId RelationGetLRelId(Relation relation);
extern void   RelationSetLockForDescriptorOpen(Relation relation);
extern void   RelationUnsetLockForRead(Relation relation);
extern void   RelationSetLockForRead(Relation relation);
extern void   LRelIdAssign(LRelId  *lRelId,
                           Oid     dbId,
                           Oid     relId);

#endif
