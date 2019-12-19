#include "storage/buf.h"
#include "storage/buf_internals.h"
#include "storage/bufmgr.h"
#include "storage/smgr.h"
#include "utils/rel.h"
#include "storage/fd.h"
#include "utils/elog.h"

extern int LateWrite;
extern int ReadBufferCount;
extern int BufferHitCount;

static Buffer ReadBufferWithBufferLock(Relation relation,
                                       BlockNumber blockNum,
                                       bool bufferLockHeld);

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
  Assert(BufferIsValid(buffer));

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

static Buffer
ReadBufferWithBufferLock(Relation    reln,
                         BlockNumber blockNum,
                         bool        bufferLockHeld){
  BufferDesc *bufHdr;
  int        extend;
  int        status;
  bool       found;
  bool       isLocalBuf;

  extend     = (blockNum == P_NEW);
  isLocalBuf = reln->rd_islocal;

  if(isLocalBuf){
    bufHdr = LocalBufferAlloc(reln, blockNum, &found);
  } else {
    ReadBufferCount++;
    bufHdr = BufferAlloc(reln, blockNum, &found, bufferLockHeld);
    if(found)
      BufferHitCount++;
  }

  if(!bufHdr){
    return (InvalidBuffer);
  }

  if(found){
    if(extend){
      memset((char *)MAKE_PTR(bufHdr->data), 0, BLCKSZ);
      (void)smgrextend(bufHdr->bufsmgr, reln, (char *)MAKE_PTR(bufHdr->data));
    }
    return (BufferDescriptorGetBuffer(bufHdr));
  }

  if(extend){
    (void)memset((char *)MAKE_PTR(bufHdr->data), 0, BLCKSZ);
    status = smgrextend(bufHdr->bufsmgr, reln, (char *)MAKE_PTR(bufHdr->data));
  } else {
    status = smgrread(bufHdr->bufsmgr, reln, blockNum,(char *)MAKE_PTR(bufHdr->data));
  }

  if(isLocalBuf)
    return (BufferDescriptorGetBuffer(bufHdr));

  SpinAcquire(BufMgrLock);

  if(status == SM_FAIL){
    if(! BufTableDelete(bufHdr)){
      SpinRelease(BufMgrLock);
      elog(FATAL, "BufRead: buffer table broken after IO error\n");
    }
    UnpinBuffer(bufHdr);

    bufHdr->flags |= BM_IO_ERROR;
    bufHdr->flags &= ~BM_IO_IN_PROGRESS;
  } else {
    bufHdr->flags &= ~(BM_IO_ERROR | BM_IO_IN_PROGRESS);
  }

  SpinRelease(BufMgrLock);

  if(status == SM_FAIL)
    return (InvalidBuffer);

  return (BufferDescriptorGetBuffer(bufHdr));
}
