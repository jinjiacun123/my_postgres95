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

static Buffer     ReadBufferWithBufferLock(Relation    relation,
                                           BlockNumber blockNum,
                                           bool        bufferLockHeld);
static int        FlushBuffer(Buffer buffer);
static BufferDesc *BufferAlloc(Relation     reln,
                               BlockNumber  blockNum,
                               bool         *foundPtr,
                               bool         bufferLockHeld);
static int        BufferReplace(BufferDesc *bufHdr,
                                bool       bufferLockHeld);
static void       WaitIO(BufferDesc *buf,
                         SPINLOCK   spinlock);
static void       SignalIO(BufferDesc *buf);

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
       AddBufferToFreelist(bufHdr);
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

static int
FlushBuffer(Buffer buffer){
  BufferDesc   *bufHdr;

  if(BufferIsLocal(buffer))
    return FlushLocalBuffer(buffer);

  if(BAD_BUFFER_ID(buffer))
    return (STATUS_ERROR);

  bufHdr = &BufferDescriptors[buffer -1];

  if(!BufferReplace(bufHdr, false)){
    elog(WARN, "FlushBuffer: cannnot flush %d", bufHdr->tag.blockNum);
    return (STATUS_ERROR);
  }

  SpinAcquire(BufMgrLock);
  bufHdr->flags &= ~BM_DIRTY;
  UnpinBuffer(bufHdr);
  SpinRelease(BufMgrLock);

  return(STATUS_OK);
}

static BufferDesc *
BufferAlloc(Relation    reln,
            BlockNumber blockNum,
            bool        *foundPtr,
            bool        bufferLockHeld){
  BufferDesc         *buf, *buf2;
  BufferTag          newTag;
  bool               inProgress;
  bool               newblock = FALSE;

  if(blockNum == P_NEW){
    newblock = TRUE;
    blockNum = smgrnblocks(reln->rd_rel->relsmgr, reln);
  }

  INIT_BUFFERTAG(&newTag, reln, blockNum);

  if(!bufferLockHeld)
    SpinAcquire(BufMgrLock);

  buf = BufTableLookup(&newTag);
  if(buf != NULL){
    PinBuffer(buf);
    inProgress = (buf->flags & BM_IO_IN_PROGRESS);

    *foundPtr = TRUE;
    if(inProgress){
      WaitIO(buf, BufMgrLock);
      if(buf->flags & BM_IO_ERROR){
        *foundPtr = FALSE;
      }
    }
    SpinRelease(BufMgrLock);

    return(buf);
  }

  *foundPtr = FALSE;
  inProgress = FALSE;
  for(buf = (BufferDesc *)NULL; buf == (BufferDesc *)NULL; ){
    buf = GetFreeBuffer();

    if( buf == NULL)
      return (NULL);

    Assert(buf->refcount == 0);
    buf->refcount = 1;
    PrivateRefCount[BufferDescriptorGetBuffer(buf) -1] = 1;

    if(buf->flags & BM_DIRTY){
      bool smok;
      inProgress = TRUE;
      buf->flags |= BM_IO_IN_PROGRESS;
      smok = BufferReplace(buf, true);

      if(smok == FALSE){
        elog(NOTICE, "BufferAlloc: cannot write block %u for %s/%s",
             buf->tag.blockNum,
             buf->sb_dbname,
             buf->sb_relname);
        inProgress = FALSE;
        buf->flags |= BM_IO_ERROR;
        buf->flags |= ~BM_IO_IN_PROGRESS;
        if(buf->refcount > 1)
          SignalIO(buf);
        PrivateRefCount[BufferDescriptorGetBuffer(buf) -1] = 0;
        buf->refcount--;
        if(buf->refcount == 0){
          AddBufferToFreelist(buf);
          buf->flags |= BM_FREE;
        }
        buf = (BufferDesc *)NULL;
      } else {
        BufferFlushCount++;
        buf->flags &= ~BM_DIRTY;
      }

      if(buf && buf->refcount > 1){
        inProgress = FALSE;
        buf->flags &= ~BM_IO_IN_PROGRESS;
        if(buf->refcount > 1)
          SignalIO(buf);
        PrivateRefCount[BufferDescriptorGetBuffer(buf) -1] = 0;
        buf->refcount--;
        buf = (BufferDesc *)NULL;
      }

      buf2 = BufTableLookup(&newTag);
      if(buf2 != NULL){
        if(buf->refcount > 1)
          SignalIO(buf);
        buf->refcount--;
        PrivateRefCount[BufferDescriptorGetBuffer(buf) -1] = 0;
        AddBufferToFreelist(buf);
        buf->flags |= BM_FREE;
        buf->flags &= ~BM_IO_IN_PROGRESS;
      }

      PinBuffer(buf2);
      inProgress = (buf2->flags & BM_IO_IN_PROGRESS);

      *foundPtr = TRUE;
      if(inProgress){
        WaitIO(buf2, BufMgrLock);
        if(buf2->flags & BM_IO_ERROR){
          *foundPtr = FALSE;
        }
      }

      SpinRelease(BufMgrLock);
      return(buf2);
    }
  }

  if(! BufTableDelete(buf)){
    SpinRelease(BufMgrLock);
    elog(FATAL, "buffer wasn't in the buffer table\n");
  }

  strcpy(buf->sb_relname, reln->rd_rel->relname.data);
  strcpy(buf->sb_dbname, GetDatabaseName());

  buf->bufsmgr = reln->rd_rel->relsmgr;

  INIT_BUFFERTAG(&(buf->tag), reln, blockNum);
  if(! BufTableInsert(buf)){
    SpinRelease(BufMgrLock);
    elog(FATAL, "Buffer in lookup table twice \n");
  }

  if(!inProgress){
    buf->flags |= BM_IO_IN_PROGRESS;
  }

  SpinRelease(BufMgrLock);

  return(buf);
}

void
IncrBufferRefCount(Buffer buffer){
  if(BufferIsLocal(buffer)){
    Assert(LocalRefCount[-buffer -1] >= 0);
    LocalRefCount[-buffer -1]++;
  } else {
    Assert(!BAD_BUFFER_ID(buffer));
    Assert(PrivateRefCount[buffer -1] >= 0);
    PrivateRefCount[buffer -1]++;
  }
}

BlockNumber
RelationGetNumberOfBlocks(Relation relation){
  return ((relation->rd_islocal) ? relation->rd_nblocks:smgrnblocks(relation->rd_rel->relsmgr, relation));
}

Buffer
RelationGetBufferWithBuffer(Relation    relation,
                            BlockNumber blockNumber,
                            Buffer      buffer){
  BufferDesc   *bufHdr;
  LRelId       lrelId;

  if(BufferIsValid(buffer)){
    if( !BufferIsLocal(buffer)){
      bufHdr = &BufferDescriptors[buffer -1];
      lrelId = RelationGetLRelId(relation);
      SpinAcquire(BufMgrLock);
      if(bufHdr->tag.blockNum == blockNumber
         && bufHdr->tag.relId.relId == lrelId.relId
         && bufHdr->tag.relId.dbId == lrelId.dbId){
        SpinRelease(BufMgrLock);
        return(buffer);
      }
      return(ReadBufferWithBufferLock(relation, blockNumber, true));
    } else {
      bufHdr = &LocalBufferDescriptors[-buffer-1];
      if(bufHdr->tag.relId.relId == relation->rd_id
         && bufHdr->tag.blockNum == blockNumber){
        return(buffer);
      }
    }
  }
  return(ReadBuffer(relation, blockNumber));
}

Buffer
ReleaseAndReadBuffer(Buffer      buffer,
                     Relation    relation,
                     BlockNumber blockNum){
  BufferDesc     *bufHdr;
  Buffer         retbuf;

  if(BufferIsLocal(buffer)){
    Assert(LocalRefCount[-buffer -1] > 0);
    LocalRefCount[-buffer -1] --;
  } else {
    if(BufferIsValid(buffer)){
      bufHdr = &BufferDescriptors[buffer -1];
      Assert(PrivateRefCount[buffer -1] > 0);
      PrivateRefCount[buffer -1] --;
      if(PrivateRefCount[buffer -1] == 0
         && LastRefCount[buffer -1] == 0){
        SpinAcquire(BufMgrLock);
        bufHdr->refcount--;
        if(bufHdr->refcount == 0){
          AddBufferToFreelist(bufHdr);
          bufHdr->flags |= BM_FREE;
        }
        retbuf = ReadBufferWithBufferLock(relation, blockNum, true);
        return retbuf;
      }
    }
  }

  return (ReadBuffer(relation, blockNum));
}

static int
BufferReplace(BufferDesc  *bufHdr,
              bool        buferLockHeld){
  Relation  reln;
  Oid       bufdb, bufrel;
  int       status;

  return (TRUE);
}

static void
WaitIO(BufferDesc *buf, SPINLOCK spinlock){

}

static void
SignalIO(BufferDesc *buf){

}
