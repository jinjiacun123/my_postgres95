#include "access/htup.h"
#include "access/skey.h"
#include "access/valid.h"
#include "access/heapam.h"
#include "utils/rel.h"
#include "utils/tqual.h"
#include "storage/itemid.h"
#include "storage/bufpage.h"
#include "fmgr.h"

HeapTuple
heap_tuple_satisfies(ItemId        itemId,
                     Relation      relation,
                     PageHeader    disk_page,
                     TimeQual      qual,
                     int           nKeys,
                     ScanKey       key){
  HeapTuple tuple;
  bool      res;

  if(! ItemIdIsUsed(itemId))
    return NULL;

  tuple = (HeapTuple) PageGetItem((Page) disk_page, itemId);

  if(key != NULL)
    res = heap_keytest(tuple,
                       RelationGetTupleDescriptor(relation),
                       nKeys,
                       key);
  else
    res = TRUE;

  if( res && (relation->rd_rel->relkind == RELKIND_UNCATALOGED
              || HeapTupleSatisfiesTimeQual(tuple, qual)))
    return tuple;

  return (HeapTuple)NULL;
}

bool
heap_keytest(HeapTuple    t,
             TupleDesc    tupdesc,
             int          nkeys,
             ScanKey      keys){
  bool   isnull;
  Datum  atp;
  int    test;

  for (; nkeys--; keys++){
    atp = (Datum) heap_getattr(t,
                               InvalidBuffer,
                               keys->sk_attno,
                               tupdesc,
                               &isnull);
    if(isnull)
      return false;

    if(keys->sk_flags & SK_COMMUTE)
      test = (long) FMGR_PTR2(keys->sk_func,
                              keys->sk_procedure,
                              keys->sk_argument,
                              atp);
    else
      test = (long) FMGR_PTR2(keys->sk_func,
                             keys->sk_procedure,
                             atp,
                             keys->sk_argument);

    if(!test == !(keys->sk_flags & SK_NEGATE))
      return false;
  }

  return true;
}
