#include "postgres.h"
#include "access/htup.h"
#include "access/tupdesc.h"
#include "access/heapam.h"
#include "access/tupmacs.h"
#include "access/transam.h"
#include "storage/buf.h"
#include "utils/elog.h"
#include "utils/nabstime.h"
#include "utils/memutils.h"

char *
heap_getattr(HeapTuple tup,
             Buffer    b,
             int       attnum,
             TupleDesc tupleDesc,
             bool      *isnull){
  bool localIsNull;

  Assert(tup != NULL);

  if(! PointerIsValid(isnull))
    isnull = &localIsNull;
  if(attnum > (int) tup->t_natts){
    *isnull = true;
    return ((char *)NULL);
  }

  if(attnum > 0){
    char *datum;
    datum = fastgetattr(tup, attnum, tupleDesc, isnull);
    return (datum);
  }

  *isnull = false;
  return heap_getsysattr(tup, b, attnum);
}

char *
fastgetattr(HeapTuple    tup,
            int           attnum,
            TupleDesc     tupleDesc,
            bool          *isnull){
  char               *tp;
  bits8              *bp;
  int                slow;
  AttributeTupleForm *att = tupleDesc->attrs;

  Assert(PointerIsvalid(isnull));
  Assert(attnum > 0);

  *isnull = false;

  if(HeapTupleNoNulls(tup)){
    attnum--;
    if(att[attnum]->attcacheoff > 0){
      return (char *)fetchatt(&(att[attnum]),
                              (char *)tup + tup->t_hoff + att[attnum]->attcacheoff);
    } else if(attnum == 0){
      return ((char *)fetchatt(&(att[0]), (char*)tup + tup->t_hoff));
    }

    tp = (char *)tup + tup->t_hoff;

    slow = 0;
  } else {
    bp   = tup->t_bits;
    tp   = (char *) tup + tup->t_hoff;
    slow = 0;
    attnum--;
    if(att_isnull(attnum, bp)){
      *isnull = true;
      return NULL;
    }
    {
      register int i = 0;
      for(i = 0; i < attnum && !slow; i++){
        if(att_isnull(i, bp))
          slow = 1;
      }
    }
  }

  if(slow){
    if(att[attnum]->attcacheoff > 0){
      return (char *)fetchatt(&(att[attnum]), tp + att[attnum]->attcacheoff);
    } else if(attnum == 0){
      return (char *)fetchatt(&(att[0]), (char *)tup + tup->t_hoff);
    } else if(!HeapTupleAllFixed(tup)){
      register int j = 0;
      for(j = 0; j< attnum && !slow; j++)
        if(att[j]->attlen < 1)
          slow = 1;
    }
  }

  if(!slow){
    register int j = 1;
    register long off;

    att[0]->attcacheoff = 0;
    while(att[j]->attcacheoff > 0)
      j++;
    off = att[j-1]->attcacheoff + att[j-1]->attlen;
    for(; j < attnum +1; j++){
      switch(att[j]->attlen){
      case -1:
        off = (att[j]->attalign == 'd') ? DOUBLEALIGN(off): INTALIGN(off);
        break;
      case sizeof(char):
        break;
      case sizeof(short):
        off = SHORTALIGN(off);
        break;
      case sizeof(int32):
        off = INTALIGN(off);
        break;
      default:
        if(att[j]->attlen < sizeof(int32)){
          elog(WARN, "fastgetattr: attribute %d has len %d", j, att[j]->attlen);
        }
        if(att[j]->attalign == 'd')
          off = DOUBLEALIGN(off);
        else
          off = LONGALIGN(off);
        break;
      }
      att[j]->attcacheoff = off;
      off += att[j]->attlen;
    }
    return (char *)fetchatt(&(att[attnum]), tp + att[attnum]->attcacheoff);
  } else {
    register bool usecache = true;
    register int  off      = 0;
    register int  i;

    for(i = 0; i < attnum; i++){
      if(!HeapTupleNoNulls(tup)){
        if(att_isnull(i, bp)){
          usecache = false;
          continue;
        }
      }
      switch(att[i]->attlen){
      case -1:
        off = (att[i]->attalign == 'd') ? DOUBLEALIGN(off): INTALIGN(off);
        break;
      case sizeof(char):
        break;
      case sizeof(short):
        off = SHORTALIGN(off);
        break;
      case sizeof(int32):
        off = INTALIGN(off);
        break;
      default:
        if(att[i]->attlen < sizeof(int32))
          elog(WARN, "fastgetatt2: attribute %d has len %d",
               i,
               att[i]->attlen);
        if(att[i]->attalign == 'd')
          off = DOUBLEALIGN(off);
        else
          off = LONGALIGN(off);
        break;
      }
      if(usecache && att[i]->attcacheoff > 0){
        off = att[i]->attcacheoff;
        if(att[i]->attlen == -1){
          usecache = false;
        }
      } else {
        if(usecache)
          att[i]->attcacheoff = off;
      }

      switch(att[i]->attlen){
      case sizeof(char):
        off++;
        break;
      case sizeof(int16):
        off += sizeof(int16);
        break;
      case sizeof(int32):
        off += sizeof(int32);
        break;
      case -1:
        usecache = false;
        off += VARSIZE(tp + off);
        break;
      default:
        off += att[i]->attlen;
        break;
      }
    }
    switch(att[attnum]->attlen){
    case -1:
      off = (att[attnum]->attalign == 'd') ? DOUBLEALIGN(off): INTALIGN(off);
      break;
    case  sizeof(char):
      break;
    case sizeof(short):
      off = SHORTALIGN(off);
      break;
    case sizeof(int32):
      off =  INTALIGN(off);
      break;
    default:
      if(att[attnum]->attlen < sizeof(int32))
        elog(WARN, "fastgetattr3: attribute %d has len %d",
             attnum,
             att[attnum]->attlen);
      if(att[attnum]->attalign == 'd')
        off = DOUBLEALIGN(off);
      else
        off = LONGALIGN(off);
    break;
    }
    return ((char *)fetchatt(&(att[attnum]), tp + off));
  }
}

char *
heap_getsysattr(HeapTuple tup,
                Buffer      b,
                int         attnum){
  switch(attnum){
  case SelfItemPointerAttributeNumber:
    return ((char *)&tup->t_ctid);
  case ObjectIdAttributeNumber:
    return ((char *)(long) tup->t_oid);
  case MinTransactionIdAttributeNumber:
    return ((char *)(long) tup->t_xmin);
  case MinCommandIdAttributeNumber:
    return ((char *)(long)tup->t_cmin);
  case MaxTransactionIdAttributeNumber:
    return ((char *)(long)tup->t_xmax);
  case MaxCommandIdAttributeNumber:
    return ((char *)(long)tup->t_cmax);
  case ChainItemPointerAttributeNumber:
    return ((char *)&tup->t_chain);
  case AnchorItemPointerAttributeNumber:
    elog(WARN, "heap_getsysattr: t_anchor does not exist!");
    break;
  case MinAbsoluteTimeAttributeNumber:
    if(!AbsoluteTimeIsBackwardCompatiblyValid(tup->t_tmin)
       && TransactionIdDidCommit(tup->t_xmin))
      tup->t_tmin = TransactionIdGetCommitTime(tup->t_xmin);
    return ((char *)(long)tup->t_tmin);
  case MaxAbsoluteTimeAttributeNumber:
    if(!AbsoluteTimeIsBackwardCompatiblyReal(tup->t_tmax)){
      if(TransactionIdDidCommit(tup->t_xmax))
        tup->t_tmax = TransactionIdGetCommitTime(tup->t_xmax);
      else
        tup->t_tmax = CURRENT_ABSTIME;
    }
    return ((char *)(long)tup->t_tmax);
  case VersionTypeAttributeNumber:
    return ((char *)(long) tup->t_vtype);
  default:
    elog(WARN, "heap_getsysattr: undefined attnum %d", attnum);
  }
  return(NULL);
}
