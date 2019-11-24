#include "postgres.h"
#include "storage/sinval.h"
#include "storage/sinvaladt.h"
#include "storage/spin.h"

SPINLOCK SInvalLock = (SPINLOCK)NULL;

void
InvalidateSharedInvalid(void (*invalFunction)(),
                        void (*resetFunction)())
{
  SpinAcquire(SInvalLock);
  SIReadEntryData(shmInvalBuffer, MyBackendId,
                  invalFunction, resetFunction);
  SIDelExpiredDataEntries(shmInvalBuffer);
  SpinRelease(SInvalLock);
}
