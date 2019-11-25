#include "storage/ipc.h"

static SLock *SLockArray = NULL;

void
ExclusiveLock(int lockid)
{
  SLock *slckP;
  slckP = &(SLockArray[lockid]);

 ex_try_again:
  S_LOCK(&(slckP->locklock));
  switch(slckP->flag){
  case NOLOCK:
    slckP->flag = EXCLUSIVELOCK;
    S_LOCK(&(slckP->exlock));
    S_LOCK(&(slckP->shlock));
    S_UNLOCK(&(slckP->locklock));
    return;
  case SHAREDLOCK:
  case EXCLUSIVELOCK:
    S_UNLOCK(&(slckP->locklock));
    S_LOCK(&(slckP->exlock));
    S_UNLOCK(&(slckP->exlock));
  }
}
