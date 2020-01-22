#include "storage/buf_internals.h"
#include "storage/bufmgr.h"
#include "storage/shmem.h"
#include "utils/elog.h"

int NLocBuffer                     = 64;
BufferDesc *LocalBufferDescriptors = NULL;
long *LocalRefCount                = NULL;
static int nextFreeLocalBuf        = 0;

int
WriteLocalBuffer(Buffer buffer,
                 bool   release){

  int bufid;

  Assert(BufferIsLocal(buffer));

  bufid = -(buffer + 1);
  LocalBufferDescriptors[bufid].flags |= BM_DIRTY;

  if(release){
    Assert(LocalRefCount[bufid] > 0);
    LocalRefCount[bufid]--;
  }

  return true;
}

BufferDesc *
LocalBufferAlloc(Relation    reln,
                 BlockNumber blockNum,
                 bool        *foundPtr){
  int        i;
  BufferDesc *bufHdr = (BufferDesc *)NULL;

  if(blockNum == P_NEW){
    blockNum = reln->rd_nblocks;
    reln->rd_nblocks++;
  }

  for(i = 0; i < NLocBuffer; i++){
    if(LocalBufferDescriptors[i].tag.relId.relId == reln->rd_id
       && LocalBufferDescriptors[i].tag.blockNum == blockNum){
      LocalRefCount[i]++;
      *foundPtr = TRUE;
      return &LocalBufferDescriptors[i];
    }
  }

  for(i = 0; i < NLocBuffer; i++){
    int b = (nextFreeLocalBuf + i) % NLocBuffer;

    if(LocalRefCount[b] == 0){
      bufHdr = &LocalBufferDescriptors[b];
      LocalRefCount[b]++;
      nextFreeLocalBuf = (b +1) % NLocBuffer;
      break;
    }
  }
  if(bufHdr == NULL)
    elog(WARN, "no empty local buffer.");

  if(bufHdr->flags & BM_DIRTY){
    Relation bufrel = RelationIdCacheGetRelation(bufHdr->tag.relId.relId);

    Assert(bufrel != NULL);

    smgrwrite(bufrel->rd_rel->relsmgr,
              bufrel,
              bufHdr->tag.blockNum,
              (char *)MAKE_PTR(bufHdr->data));
  }

  bufHdr->tag.relId.relId  = reln->rd_id;
  bufHdr->tag.blockNum     = blockNum;
  bufHdr->flags            &= ~BM_DIRTY;

  if(bufHdr->data == (SHMEM_OFFSET)0){
    char *data = (char *)malloc(BLCKSZ);
    bufHdr->data = MAKE_OFFSET(data);
  }

  *foundPtr = FALSE;
  return bufHdr;
}

int
FlushLocalBuffer(Buffer buffer){
  int        bufid;
  Relation   bufrel;
  BufferDesc *bufHdr;

  Assert(BufferIsLocal(buffer));

}
