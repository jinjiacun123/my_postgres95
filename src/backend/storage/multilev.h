#ifndef MULTILEV_H
#define MULTILEV_H

#include "storage/lock.h"

typedef int LOCK_LEVEL;
#define READ_LOCK 2

#define RELN_LEVEL 0



extern bool MultiLockRel(LockInfo linfo,
                         LOCKT    lockt);
extern bool MultiRelease(LockTableId tableId,
                         LOCKTAG     *tag,
                         LOCKT       lockt,
                         LOCK_LEVEL  level);
extern bool MultiAcquire(LockTableId tableId,
                         LOCKTAG     *tag,
                         LOCKT       lockt,
                         LOCK_LEVEL  level);
#endif
