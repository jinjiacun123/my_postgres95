#ifndef BUF_INTERNALS_H
#define BUF_INTERNALS_H
#include "postgres.h"
#include "storage/shmem.h"
#include "storage/lmgr.h"
#include "storage/buf.h"

#define NDBUFS 64

int    BufferFlushCount;

typedef bits16          BufFlags;

#define BM_DIRTY          (1 << 0)
#define BM_FREE           (1 << 4)
#define BM_DELETED        (1 << 3)
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

#define INIT_BUFFERTAG(a, xx_reln, xx_blockNum) {   \
    (a)->blockNum = xx_blockNum;                    \
    (a)->relId    = RelationGetLRelId(xx_reln);     \
  }

struct sbufdesc {
  Buffer       freeNext;
  Buffer       freePrev;
  SHMEM_OFFSET data;
  BufferTag    tag;
  BufFlags     flags;
  unsigned     refcount;
  int16        bufsmgr;
  int          buf_id;
  char         sb_dbname[NAMEDATALEN + 1];
  char         sb_relname[NAMEDATALEN + 1];
} ;

extern long       *PrivateRefCount;
extern long       *LocalRefCount;
extern BufferDesc *LocalBufferDescriptors;
extern  int       NLocBuffer;
extern BufferDesc *BufferDescriptors;
extern long       *LastRefCount;
extern SPINLOCK   BufMgrLock;
extern int        Free_List_Descriptor;

extern int        WriteLocalBuffer(Buffer buffer, bool release);
extern void       unpinBuffer(BufferDesc *buf);
extern BufferDesc *LocalBufferAlloc(Relation    reln,
                                    BlockNumber blockNum,
                                    bool        *foundPtr);
extern bool       BufTableDelete(BufferDesc *buf);
extern int        FlushLocalBuffer(Buffer buffer);
extern BufferDesc *BufTableLookup(BufferTag *tagPtr);
extern void       PinBuffer(BufferDesc *buf);
extern BufferDesc *GetFreeBuffer(void);
extern bool       BufTableInsert(BufferDesc *buf);
#endif
