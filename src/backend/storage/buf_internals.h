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
  int16        bufsmgr;
} ;

#define BM_DIRTY          (1 << 0)
#define BM_FREE           (1 << 4)
#define BM_IO_IN_PROGRESS (1 << 5)
#define BM_IO_ERROR       (1 << 6)

typedef struct sbufdesc BufferDesc;
typedef struct buftag   BufferTag;

extern int NBuffers;

#define BAD_BUFFER_ID(bid) ((bid<1) || (bid >(NBuffers)))

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
