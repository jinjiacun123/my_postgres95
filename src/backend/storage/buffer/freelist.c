#include "storage/buf_internals.h"
#include "storage/bufmgr.h"

#define NotInQueue(bf)\
  Assert((bf->freeNext == INVALID_DESCRIPTOR)); \
  Assert((bf->freePrev == INVALID_DESCRIPTOR)); \
  Assert((bf->flags & BM_FREE))

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

void
PinBuffer(BufferDesc *buf){

}

BufferDesc *
GetFreeBuffer(){
  BufferDesc *buf;

  return(buf);
}
