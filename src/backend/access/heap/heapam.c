#include "utils/rel.h"
#include "utils/elog.h"
#include "utils/tqual.h"
#include "utils/relcache.h"
#include "access/heapam.h"
#include "access/relscan.h"
#include "access/htup.h"
#include "access/skey.h"
#include "access/valid.h"
#include "storage/buf.h"
#include "storage/smgr.h"
#include "storage/bufmgr.h"
#include "storage/itemid.h"
#include "storage/bufpage.h"
#include "storage/lock.h"
#include "storage/itemptr.h"
#include "storage/off.h"
#include "catalog/catalog.h"

#define HEAPDEBUG_1
#define HEAPDEBUG_2
#define HEAPDEBUG_3
#define HEAPDEBUG_4
#define HEAPDEBUG_5
#define HEAPDEBUG_6
#define HEAPDEBUG_7

static void unpinsdesc(HeapScanDesc sdesc);
static void initsdesc(HeapScanDesc  sdesc,
                      Relation      relation,
                      int           atend,
                      unsigned      nkeys,
                      ScanKey       key);
static int nextpage(int page,
                    int  dir);
static HeapTuple
heapgettup(Relation    relation,
           ItemPointer tid,
           int         dir,
           Buffer      *b,
           TimeQual    timeQual,
           int         nkeys,
           ScanKey     key);

Relation
heap_openr(char *relationName){
  Relation r;

  IncrHeapAccessStat(local_openr);
  IncrHeapAccessStat(global_openr);
  r = RelationNameGetRelation(relationName);
  if(RelationIsValid(r) && r->rd_rel->relkind == RELKIND_INDEX){
    elog(WARN, "%s is an index relation", r->rd_rel->relname.data);
  }

  return r;
}

void
heap_close(Relation relation){
  IncrHeapAccessStat(local_close);
  IncrHeapAccessStat(global_close);

  (void) RelationClose(relation);
}

void
heap_endscan(HeapScanDesc sdesc){
  IncrHeapAccessStat(local_endscan);
  IncrHeapAccessStat(global_endscan);

  unpinsdesc(sdesc);

  RelationDecrementReferenceCount(sdesc->rs_rd);

  if(IsSystemRelationName(RelationGetRelationName(sdesc->rs_rd)->data))
    RelationUnsetLockForRead(sdesc->rs_rd);

  pfree(sdesc);
}

HeapScanDesc
heap_beginscan(Relation relation,
               int      atend,
               TimeQual timeQual,
               unsigned nkeys,
               ScanKey  key){
  HeapScanDesc sdesc;
  IncrHeapAccessStat(local_beginscan);
  IncrHeapAccessStat(global_beginscan);

  if(RelationIsValid(relation) == false)
    elog(WARN, "heap_beginscan: !RelationIsValid(relation)");

  RelationSetLockForRead(relation);

  if(relation->rd_rel->relkind == RELKIND_UNCATALOGED){
    timeQual = SelfTimeQual;
  }

  RelationIncrementReferenceCount(relation);
  sdesc = (HeapScanDesc) palloc(sizeof(HeapScanDescData));
  relation->rd_nblocks = smgrnblocks(relation->rd_rel->relsmgr, relation);
  sdesc->rs_rd = relation;

  if(nkeys){
    sdesc->rs_key = (ScanKey) palloc(sizeof(ScanKeyData) * nkeys);
  } else {
    sdesc->rs_key = NULL;
  }

  initsdesc(sdesc, relation, atend, nkeys, key);
  sdesc->rs_atend = atend;
  sdesc->rs_tr    = timeQual;
  sdesc->rs_nkeys = (short)nkeys;

  return (sdesc);
}


HeapTuple
heap_getnext(HeapScanDesc scandesc,
             int           backw,
             Buffer        *b){
  register HeapScanDesc sdesc = scandesc;
  Buffer                localb;

  IncrHeapAccessStat(local_getnext);
  IncrHeapAccessStat(global_getnext);

  if(sdesc == NULL)
    elog(WARN, "heap_getnext: NULL relscan");

  if(! PointerIsValid(b))
    b = &localb;
  (*b) = InvalidBuffer;

  HEAPDEBUG_1;

  if(backw){
    HEAPDEBUG_2;
    if(sdesc->rs_ptup == sdesc->rs_ctup
       && BufferIsValid(sdesc->rs_pbuf)){
      if(BufferIsValid(sdesc->rs_nbuf))
        ReleaseBuffer(sdesc->rs_nbuf);
      return (NULL);
    }

    if(sdesc->rs_nbuf != sdesc->rs_cbuf){
      if(BufferIsValid(sdesc->rs_nbuf))
        ReleaseBuffer(sdesc->rs_nbuf);
      if(BufferIsValid(sdesc->rs_cbuf))
        IncrBufferRefCount(sdesc->rs_cbuf);
    }
    sdesc->rs_ntup = sdesc->rs_ctup;
    sdesc->rs_nbuf = sdesc->rs_cbuf;

    if(sdesc->rs_ptup != NULL){
      if(sdesc->rs_cbuf != sdesc->rs_pbuf){
        if(BufferIsValid(sdesc->rs_cbuf))
          ReleaseBuffer(sdesc->rs_cbuf);
        if(BufferIsValid(sdesc->rs_pbuf))
          IncrBufferRefCount(sdesc->rs_pbuf);
      }
      sdesc->rs_ctup = sdesc->rs_ptup;
      sdesc->rs_cbuf = sdesc->rs_pbuf;
    } else {
      ItemPointer iptr;

      iptr = (sdesc->rs_ctup != NULL) ? &(sdesc->rs_ctup->t_ctid):(ItemPointer)NULL;
      sdesc->rs_ctup = (HeapTuple)heapgettup(sdesc->rs_rd,
                                             iptr,
                                             -1,
                                             &(sdesc->rs_cbuf),
                                             sdesc->rs_tr,
                                             sdesc->rs_nkeys,
                                             sdesc->rs_key);
    }

    if(sdesc->rs_ctup == NULL && !BufferIsValid(sdesc->rs_cbuf)){
      if(BufferIsValid(sdesc->rs_pbuf))
        ReleaseBuffer(sdesc->rs_pbuf);
      sdesc->rs_ptup = NULL;
      sdesc->rs_pbuf = InvalidBuffer;
      if(BufferIsValid(sdesc->rs_nbuf))
        ReleaseBuffer(sdesc->rs_nbuf);
      sdesc->rs_ntup = NULL;
      sdesc->rs_nbuf = InvalidBuffer;
      return (NULL);
    }

    if(BufferIsValid(sdesc->rs_pbuf))
      ReleaseBuffer(sdesc->rs_pbuf);
    sdesc->rs_ptup = NULL;
    sdesc->rs_pbuf = UnknownBuffer;
  } else {
    if(sdesc->rs_ctup == sdesc->rs_ntup
       && BufferIsValid(sdesc->rs_nbuf)){
      if(BufferIsValid(sdesc->rs_pbuf))
        ReleaseBuffer(sdesc->rs_pbuf);
      HEAPDEBUG_3;
      return (NULL);
    }

    if(sdesc->rs_pbuf != sdesc->rs_cbuf){
      if(BufferIsValid(sdesc->rs_pbuf))
        ReleaseBuffer(sdesc->rs_pbuf);
      if(BufferIsValid(sdesc->rs_cbuf))
        IncrBufferRefCount(sdesc->rs_cbuf);
    }
    sdesc->rs_ptup = sdesc->rs_ctup;
    sdesc->rs_pbuf = sdesc->rs_cbuf;

    if(sdesc->rs_ntup != NULL){
      if(sdesc->rs_cbuf != sdesc->rs_nbuf){
        if(BufferIsValid(sdesc->rs_cbuf))
          ReleaseBuffer(sdesc->rs_cbuf);
        if(BufferIsValid(sdesc->rs_nbuf))
          IncrBufferRefCount(sdesc->rs_nbuf);
      }
      sdesc->rs_ctup = sdesc->rs_ntup;
      sdesc->rs_cbuf = sdesc->rs_nbuf;
      HEAPDEBUG_5;
    } else {
      ItemPointer iptr;

      iptr = (sdesc->rs_ctup != NULL) ?
        &(sdesc->rs_ctup
               ->t_ctid): (ItemPointer)NULL;
      sdesc->rs_ctup = (HeapTuple)heapgettup(sdesc->rs_rd,
                                             iptr,
                                             1,
                                             &sdesc->rs_cbuf,
                                             sdesc->rs_tr,
                                             sdesc->rs_nkeys,
                                             sdesc->rs_key);
    }

    if(sdesc->rs_ctup == NULL && !BufferIsValid(sdesc->rs_cbuf)){
      if(BufferIsValid(sdesc->rs_nbuf))
        ReleaseBuffer(sdesc->rs_nbuf);
      sdesc->rs_ntup = NULL;
      sdesc->rs_nbuf = InvalidBuffer;
      if(BufferIsValid(sdesc->rs_pbuf))
        ReleaseBuffer(sdesc->rs_pbuf);
      sdesc->rs_ptup = NULL;
      sdesc->rs_pbuf = InvalidBuffer;
      HEAPDEBUG_6;
      return (NULL);
    }

    if(BufferIsValid(sdesc->rs_nbuf))
      ReleaseBuffer(sdesc->rs_nbuf);
    sdesc->rs_ntup = NULL;
    sdesc->rs_nbuf = UnknownBuffer;
  }

  (*b) = sdesc->rs_cbuf;
  HEAPDEBUG_7;

  return (sdesc->rs_ctup);
}

static void
unpinsdesc(HeapScanDesc sdesc){
  if(BufferIsValid(sdesc->rs_pbuf)){
    ReleaseBuffer(sdesc->rs_pbuf);
  }

  if(BufferIsValid(sdesc->rs_cbuf)){
    ReleaseBuffer(sdesc->rs_cbuf);
  }

  if(BufferIsValid(sdesc->rs_nbuf)){
    ReleaseBuffer(sdesc->rs_nbuf);
  }
}

static void
initsdesc(HeapScanDesc  sdesc,
          Relation      relation,
          int           atend,
          unsigned      nkeys,
          ScanKey       key){
  if(!RelationGetNumberOfBlocks(relation)){
    sdesc->rs_ntup = sdesc->rs_ctup = sdesc->rs_ptup = NULL;
    sdesc->rs_nbuf = sdesc->rs_cbuf = sdesc->rs_pbuf = InvalidBuffer;
  } else if(atend){
    sdesc->rs_ntup = sdesc->rs_ctup = NULL;
    sdesc->rs_nbuf = sdesc->rs_cbuf = InvalidBuffer;
    sdesc->rs_ptup = NULL;
    sdesc->rs_pbuf = UnknownBuffer;
  } else {
    sdesc->rs_ctup = sdesc->rs_ptup = NULL;
    sdesc->rs_cbuf = sdesc->rs_pbuf = InvalidBuffer;
    sdesc->rs_ntup = NULL;
    sdesc->rs_nbuf = UnknownBuffer;
  }

  ItemPointerSetInvalid(&(sdesc->rs_mptid));
  ItemPointerSetInvalid(&(sdesc->rs_mctid));
  ItemPointerSetInvalid(&(sdesc->rs_mntid));
  ItemPointerSetInvalid(&(sdesc->rs_mcd));

  if(key != NULL)
    memmove(sdesc->rs_key, key, nkeys * sizeof(ScanKeyData));
}

static HeapTuple
heapgettup( Relation    relation,
            ItemPointer tid,
            int         dir,
            Buffer      *b,
            TimeQual    timeQual,
            int         nkeys,
            ScanKey     key){
  ItemId              lpp;
  Page                dp;
  int                 page;
  int                 pages;
  int                 lines;
  HeapTuple           rtup;
  OffsetNumber        lineoff;
  int                 linesleft;

  IncrHeapAccessStat(local_heapgettup);
  IncrHeapAccessStat(global_heapgettup);

  if(!ItemPointerIsValid(tid)){
    Assert(!PointerIsValid(tid));
  }

  if( !(pages = relation->rd_nblocks))
    return (NULL);

  if(!dir){
    if(ItemPointerIsValid(tid) == false){
      *b = InvalidBuffer;
      return (NULL);
    }
    *b = RelationGetBufferWithBuffer(relation,
                                     ItemPointerGetBlockNumber(tid),
                                     *b);
    dp      = (Page) BufferGetPage(*b);
    lineoff = ItemPointerGetOffsetNumber(tid);
    lpp     = PageGetItemId(dp, lineoff);

    rtup    = (HeapTuple)PageGetItem((Page)dp, lpp);
    return (rtup);
  } else if(dir < 0){
    if( ItemPointerIsValid(tid) == false){
      tid = NULL;
    }
    if( tid == NULL){
      page = pages -1;
    } else {
      page = ItemPointerGetBlockNumber(tid);
    }
    if(page < 0){
      *b = InvalidBuffer;
      return (NULL);
    }

    *b    = RelationGetBufferWithBuffer(relation, page, *b);
    dp    = (Page) BufferGetPage(*b);
    lines = PageGetMaxOffsetNumber(dp);
    if(tid == NULL){
      lineoff = lines;
    } else {
      lineoff = OffsetNumberPrev(ItemPointerGetOffsetNumber(tid));
    }
  } else {
    if(ItemPointerIsValid(tid) == false){
      page    = 0;
      lineoff = FirstOffsetNumber;
    } else {
      page    = ItemPointerGetBlockNumber(tid);
      lineoff = OffsetNumberNext(ItemPointerGetOffsetNumber(tid));
    }

    if(page >= pages){
      *b = InvalidBuffer;
      return (NULL);
    }
    *b = RelationGetBufferWithBuffer(relation, page, *b);

    dp     = (Page) BufferGetPage(*b);
    lines  = PageGetMaxOffsetNumber(dp);
  }

  lpp = PageGetItemId(dp, lineoff);
  if(dir < 0){
    linesleft = lineoff -1;
  } else {
    linesleft = lines - lineoff;
  }

  for(;;){
    while( linesleft >= 0){
      if((rtup = heap_tuple_satisfies(lpp,
                                       relation,
                                       (PageHeader) dp,
                                       timeQual,
                                       nkeys,
                                      key)) != NULL){
        ItemPointer iptr = &(rtup->t_ctid);
        if(ItemPointerGetBlockNumber(iptr) != page){
          ItemPointerSetBlockNumber(iptr, page);
        }
        return (rtup);
      }

      --linesleft;
      if( dir < 0){
        --lpp;
      } else {
        ++lpp;
      }
    }

    page = nextpage(page, dir);
    if( page < 0 || page >= pages){
      if( BufferIsValid(*b))
        ReleaseBuffer(*b);
      *b = InvalidBuffer;
      return (NULL);
    }
    *b = ReleaseAndReadBuffer(*b, relation, page);

    dp    = (Page) BufferGetPage(*b);
    lines = lineoff = PageGetMaxOffsetNumber((Page)dp);
    linesleft = lines -1;
    if( dir < 0){
      lpp = PageGetItemId(dp, lineoff);
    } else {
      lpp = PageGetItemId(dp, FirstOffsetNumber);
    }
  }
}

static int
nextpage(int page, int dir){
  return((dir  < 0)? page -1: page +1);
}
