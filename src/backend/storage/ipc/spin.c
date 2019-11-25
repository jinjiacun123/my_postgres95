#include "storage/ipc.h"
#include "storage/spin.h"

void
SpinAcquire(SPINLOCK lock)
{
  ExclusiveLock(lock);
  //PROC_INCR_SLOCK(lock);
}

void
SpinRelease(SPINLOCK lock)
{

}
