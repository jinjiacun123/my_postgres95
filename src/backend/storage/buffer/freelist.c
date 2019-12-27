#include "storage/buf_internals.h"

static BufferDesc *SharedFreeList;

void
AddBufferToFreelist(BufferDesc *bf){
  NotInQueue(bf);

  bf->freePrev = SharedFreeList->freePrev;
  bf->freeNext = Free_List_Descriptor;

  BufferDescriptors[bf->freeNext].freePrev = bf->buf_id;
  BufferDescriptors[bf->freePrev].freeNext = bf->buf_id;
}

void
UnpinBuffer(BufferDesc *buf){
  long b = BufferDescriptorGetBuffer(buf) - 1;

  Assert(buf->refcount);
  Assert(PrivateRefCount[b] > 0);
  PrivateRefCount[b]--;
  if(PrivateRefCount[b] == 0
     && LastRefCount[b] == 0)
    buf->refcount--;
  NotInQueue(buf);

  if(buf->refcount == 0){
    AddBufferToFreelist(buf);
    buf->flags |= BM_FREE;
  } else {

  }
}
