#ifndef BUF_INTERNALS_H
#define BUF_INTERNALS_H
#include "postgres.h"
#include "storage/shmem.h"
#include "storage/lmgr.h"

typedef bits16          BufFlags;
struct sbufdesc {
  SHMEM_OFFSET data;
  BufFlags     flags;
  unsigned     refcount;
} ;

#define BM_FREE (1 << 4)

typedef struct sbufdesc BufferDesc;
typedef struct buftag   BufferTag;

struct buftag {
  LRelId      relId;
  BlockNumber blockNum;
};

extern long       *PrivateRefCount;
extern long       *LocalRefCount;
extern BufferDesc *LocalBufferDescriptors;
extern  int       NLocBuffer;
extern BufferDesc *BufferDescriptors;
extern long       *LastRefCount;
extern SPINLOCK   BufMgrLock;
#endif
