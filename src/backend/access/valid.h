#ifndef VALID_H
#define VALID_H
#include "access/htup.h"
#include "utils/rel.h"
#include "utils/tqual.h"
#include "storage/itemid.h"
#include "storage/bufpage.h"


extern HeapTuple heap_tuple_satisfies(ItemId     itemId,
                                      Relation   relation,
                                      PageHeader disk_page,
                                      TimeQual   qual,
                                      int        nKeys,
                                      ScanKey    key);
extern  bool  heap_keytest(HeapTuple   t,
                           TupleDesc   tupdesc,
                           int         nkeys,
                           ScanKey     kyes);

#endif
