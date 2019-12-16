#include "storage/buf.h"
#include "storage/buf_internals.h"
#include "storage/bufmgr.h"
#include "utils/rel.h"
#include "storage/fd.h"

extern int LateWrite;

Buffer
ReadBuffer(Relation reln, BlockNumber blockNum){
  return ReadBufferWithBufferLock(reln, blockNum, false);
}

bool
BufferIsValid(Buffer bufnum){
  if(BufferIsLocal(bufnum))
    return (bufnum>= -NLocBuffer && LocalRefCount[bufnum -1] >0);
  if(BAD_BUFFER_ID(bufnum))
    return (false);

  return ((bool)(PrivateRefCount[bufnum - 1] > 0));
}

Block
BufferGetBlock(Buffer buffer){
  Assert(bufferIsValid(buffer));

  if(BufferIsLocal(buffer))
    return ((Block)MAKE_PTR(LocalBufferDescriptors[-buffer-1].data));
  else
    return ((Block)MAKE_PTR(BufferDescriptors[buffer-1].data));
}

int
ReleaseBuffer(Buffer buffer){
  BufferDesc *bufHdr;

  if(BufferIsLocal(buffer)){
    Assert(LocalRefCount[-buffer-1] > 0);
    LocalRefCount[-buffer-1]--;
    return (STATUS_OK);
  }

  if(BAD_BUFFER_ID(buffer))
    return(STATUS_ERROR);

  bufHdr = &BufferDescriptors[buffer -1];

  Assert(PrivateRefCount[buffer -1] > 0);
  PrivateRefCount[buffer-1]--;
  if(PrivateRefCount[buffer-1] == 0 && LastRefCount[buffer-1] == 0){
    SpinAcquire(BufMgrLock);
    bufHdr->refcount--;
    if(bufHdr->refcount == 0){
       AddBufferToFreeList(bufHdr);
       bufHdr->flags |= BM_FREE;
    }
    SpinRelease(BufMgrLock);
  }

  return(STATUS_OK);
}

int
WriteBuffer(Buffer buffer){
   BufferDesc *bufHdr;

  if(! LateWrite){
    return (FlushBuffer(buffer));
  } else {
    if(BufferIsLocal(buffer))
      return WriteLocalBuffer(buffer, TRUE);

    if(BAD_BUFFER_ID(buffer))
      return (FALSE);

    bufHdr = &BufferDescriptors[buffer -1];

    SpinAcquire(BufMgrLock);
    Assert(bufHdr->refcount > 0);
    bufHdr->flags |= BM_DIRTY;
    UnpinBuffer(bufHdr);
    SpinRelease(BufMgrLock);
  }
  return (TRUE);
}
