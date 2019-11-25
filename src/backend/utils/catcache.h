#ifndef CATCACHE_H
#define CATCACHE_H
#include "postgres.h"
#include "access/skey.h"
#include "access/htup.h"
#include "utils/rel.h"
#include "nodes/memnodes.h"
#include "lib/dllist.h"


extern void ResetSystemCache(void);

#define NCCBUCK 500

typedef struct catcache {
  Oid             relationId;
  Oid             indexId;
  char            *cc_relname;
  char            *cc_indname;
  HeapTuple       (*cc_iscanfunc)();
  TupleDesc       cc_tupdess;
  int             id;
  short           cc_ntup;
  short           cc_maxtup;
  short           cc_nkeys;
  short           cc_size;
  short           cc_key[4];
  short           cc_klen[4];
  ScanKeyData     cc_skey[4];
  struct catcache *cc_next;
  Dllist          *cc_lrulist;
  Dllist          *cc_cache[NCCBUCK+1];
} CatCache;

#endif
