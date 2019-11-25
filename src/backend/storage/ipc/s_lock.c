#include "storage/ipc.h"

int
tas(slock_t *m)
{
  slock_t res;
  __asm__("xchgb %0,%1":"=q"(res),"=m"(*m):"0"(0x1));
  return(res);
}

void
S_LOCK(slock_t *lock)
{
  while(tas(lock))
    ;
}

void
S_UNLOCK(slock_t *lock)
{
  *lock = 0;
}

