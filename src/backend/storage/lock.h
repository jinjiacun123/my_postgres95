#ifndef LOCK_H
#define LOCK_H
#include "postgres.h"
#include "storage/itemptr.h"

typedef int LOCKT;
typedef int LockTableId;

typedef struct ltag {
  Oid              relId;
  Oid              dbId;
  ItemPointerData  tupleId;
} LOCKTAG;








#endif
