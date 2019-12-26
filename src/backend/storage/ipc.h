#ifndef IPC_H
#define IPC_H

#include "c.h"

typedef int IpcSemaphoreId;

typedef unsigned char slock_t;

typedef struct slock{
  slock_t       locklock;
  unsigned char flag;
  short         nshlocks;
  slock_t       shlock;
  slock_t       exlock;
  slock_t       comlock;
  struct slock  *next;
} SLock;

#define NOLOCK        0
#define SHAREDLOCK    1
#define EXCLUSIVELOCK 2

typedef uint32  IpcMemoryKey;
typedef int     IpcMemoryId;

extern void ExclusiveLock(int lockid);
extern void S_LOCK(slock_t *lock);

#endif
