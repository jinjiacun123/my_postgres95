#include "postgres.h"
#include "utils/nabstime.h"
#include "utils/tqual.h"
#include "utils/rel.h"
#include "utils/elog.h"
#include "access/htup.h"
#include "access/transam.h"

typedef uint16  TimeQualMode;

typedef struct TimeQualData {
  AbsoluteTime     start;
  AbsoluteTime     end;
  TimeQualMode     mode;
} TimeQualData;

typedef TimeQualData  *InternalTimeQual;

static TimeQualData   SelfTimeQualData;
TimeQual              SelfTimeQual = (Pointer)&SelfTimeQualData;

bool
HeapTupleSatisfiesTimeQual(HeapTuple  tuple,
                           TimeQual      qual){

  Assert(HeapTupleIsValid(tuple));
  Assert(TimeQualIsValid(qual));

  if(TransactionIdEquals(tuple->t_xmax, AmiTransactionId))
    return (false);

  if(qual == SelfTimeQual
     || heapisoverride()){
    return (HeapTupleSatisfiesItself(tuple));
  }

  if(qual == NowTimeQual){
    return (HeapTupleSatisfiesNow(tuple));
  }

  if(!TimeQualIsLegal(qual)){
    elog(WARN, "HeapTupleSatisfiesTimeQual: illegal time qual");
  }

  if(TimeQualIndicateDisableValidityChecking(qual)){
    elog(WARN, "HeapTupleSatisfiesTimeQual: no disabled validity checking (yet)");
  }

  if(TimeQualIsSnapshot(qual)){
    return (HeapTupleSatisfiesSnapshotInternalTimeQual(tuple,
                                                       (InternalTimeQual)qual));
  }

  if(TimeQualIncludesNow(qual)){
    return (HeapTupleSatisfiesUpperUnboundedInternalTimeQual(tuple,
                                                             (InternalTimeQual)qual));
  }
  return (HeapTupleSatisfiesUpperBoundedInternalTimeQual(tuple,
                                                         (InternalTimeQual)qual));
}
