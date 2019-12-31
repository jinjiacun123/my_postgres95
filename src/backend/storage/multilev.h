#ifndef MULTILEV_H
#define MULTILEV_H

#include "storage/lock.h"

#define READ_LOCK 2

#define RELN_LEVEL 0



extern bool MultiLockRel(LockInfo linfo,
                         LOCKT    lockt);

#endif
