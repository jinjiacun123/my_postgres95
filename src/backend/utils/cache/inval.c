#include "postgres.h"
#include "storage/sinval.h"
#include "utils/catcache.h"

static void
ResetSystemCaches(){
  ResetSystemCache();
  RelationCacheInvalidate(false);
}

static void
CacheInvalidate(Index       cacheId,
                Index       hashIndex,
                ItemPointer pointer)
{

}

void
DiscardInvalid(){
  InvalidateShareInvalid(CacheInvalidate, ResetSystemCaches);
}
