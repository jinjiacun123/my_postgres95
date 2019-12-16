#ifndef LMGR_H
#define LMGR_H
#include "postgres.h"
#include "storage/itemptr.h"
#include "nodes/memnodes.h"

typedef struct LRelId {
  Oid relId;
  Oid dbId;
} LRelId;
#endif
