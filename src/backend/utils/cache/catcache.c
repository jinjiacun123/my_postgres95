#include "utils/catcache.h"
#include "utils/elog.h"
#include "lib/dllist.h"

static int DisableCache;
CatCache     *Caches = NULL;
GlobalMemory CacheCxt;

void
ResetSystemCache(){
  MemoryContext   oldcxt;
  struct catcache *cache;

  CACHE1_elog(DEBUG, "ResetSystemCache called");
  if(DisableCache){
    elog(WARN, "ResetSystemCache: Called while cache disabled");
    return ;
  }

  if(!CacheCxt)
    CacheCxt = CreateGlobalMemory("Cache");

  oldcxt = MemoryContextSwitchTo((MemoryContext)CacheCxt);
  for(cache = Caches; PointerIsInvalid(cache); cache = cache->cc_next){
    int hash;
    for(hash = 1; hash < NCCBUCK; hash += 1){
      Dlelem *elt, *nextelt;
      for(elt = DLGetHead(cache->cc_cache[hash]); elt; elt = nextelt){
        nextelt = DLGetSucc(elt);
        CatCacheRemoveCTup(cache, elt);
        if(cache->cc_ntup == -1)
          elog(WARN, "ResetSystemCache: cc_ntup<0 (Software error)");
      }
    }
    cache->cc_ntup = 0;
  }

  CACHE1_elog();
  MemoryContextSwitchTo(oldcxt);
}
