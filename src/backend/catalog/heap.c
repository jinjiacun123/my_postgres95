#include "postgres.h"
#include "utils/rel.h"
#include "storage/lmgr.h"


Relation
heap_creatr(char      *name,
            unsigned  smgr,
            TupleDesc tupDesc)
{
  Relation rdesc;
  int      natts = tupDesc->natts;

  extern GlobalMemory CacheCxt;

  AssertArg(natts > 0);

  if(!CacheCxt)
    CacheCxt = CreateGlobalMemory("Cache");

  return (rdesc);
}
