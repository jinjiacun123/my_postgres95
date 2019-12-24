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

extern void RelationSetLockForDescriptorOpen(Relation relation);

#endif
