#include "access/attnum.h"
#include "access/strat.h"
#include "catalog/pg_amop.h"
#include "storage/buf.h"
#include "catalog/catname.h"
#include "catalog/pg_amproc.h"
#include "catalog/pg_index.h"
#include "catalog/pg_operator.h"
#include "utils/elog.h"
#include "utils/tqual.h"
#include "catalog/pg_proc.h"
#include "access/itup.h"
#include "access/htup.h"
#include "utils/rel.h"
#include "access/relscan.h"
#include "access/istrat.h"
#include "access/skey.h"

static void
OperatorRelationFillScanKeyEntry(Relation operatorRelation,
                                 Oid      operatorObjectId,
                                 ScanKey  entry);

void
IndexSupportInitialize(IndexStrategy  indexStrategy,
                       RegProcedure   *indexSupport,
                       Oid            indexObjectId,
                       Oid            accessMethodObjectId,
                       StrategyNumber maxStrategyNumber,
                       StrategyNumber maxSupportNumber,
                       AttrNumber     maxAttributeNumber){
  Relation     relation;
  Relation     operatorRelation;
  HeapScanDesc scan;
  HeapTuple    tuple;
  ScanKeyData  entry[2];
  StrategyMap  map;
  AttrNumber   attributeNumber;

  Oid         operatorClassObjectId[MaxIndexAttributeNumber];
  int         attributeIndex;
  maxStrategyNumber = AMStrategies(maxStrategyNumber);

  ScanKeyEntryInitialize(&entry[0],
                         0,
                         Anum_pg_index_indexrelid,
                         ObjectIdEqualRegProcedure,
                         ObjectIdGetDatum(indexObjectId));
  relation = heap_openr(IndexRelationName);
  scan     = heap_beginscan(relation,
                            false,
                            NowTimeQual,
                            1,
                            entry);
  tuple = heap_getnext(scan,
                       0,
                       (Buffer *)NULL);
  if(! HeapTupleIsValid(tuple))
    elog(WARN, "IndexSupportInitialize: corrupted catalogs");

  for(attributeIndex = 0;
      attributeIndex < maxAttributeNumber;
      attributeIndex++){
    IndexTupleForm iform;
    iform = (IndexTupleForm) GETSTRUCT(tuple);

    if(!OidIsValid(iform->indkey[attributeIndex])){
      if(attributeIndex == -1){
        elog(WARN, "IndexSupportInitialize: no pg_indetuple");
      }
      break;
    }

    operatorClassObjectId[attributeIndex] = iform->indclass[attributeIndex];
  }

  heap_endscan(scan);
  heap_close(relation);

  if(maxSupportNumber > 0){
    ScanKeyEntryInitialize(&entry[0],
                           0,
                           Anum_pg_amproc_amid,
                           ObjectIdEqualRegProcedure,
                           ObjectIdGetDatum(accessMethodObjectId));
    ScanKeyEntryInitialize(&entry[1],
                           0,
                           Anum_pg_amproc_amopclaid,
                           ObjectIdEqualRegProcedure,
                           0);
    relation = heap_openr(AccessMethodProcedureRelationName);
    for(attributeNumber = maxAttributeNumber;
        attributeNumber > 0;
        attributeNumber --){
      int16          support;
      Form_pg_amproc form;
      RegProcedure   *loc;

      loc = &indexSupport[((attributeNumber -1) * maxSupportNumber)];

      for(support = maxSupportNumber;
          --support >= 0;){
        loc[support] = InvalidOid;
      }

      entry[1].sk_argument = ObjectIdGetDatum(operatorClassObjectId[attributeNumber -1]);
      scan = heap_beginscan(relation,
                            false,
                            NowTimeQual,
                            2,
                            entry);
      while(tuple = heap_getnext(tuple = heap_getnext(scan, 0, (Buffer*)NULL)),
                                 HeapTupleIsValid(tuple)){
              form = (Form_pg_amproc)GETSTRUCT(tuple);
              loc[(form->amprocnum -1)] = form->amproc;
            }
            heap_endscan(scan);
            }
      heap_close(relation);
  }
    ScanKeyEntryInitialize(&entry[0],
                           0,
                           Anum_pg_amop_amopid,
                           ObjectIdEqualRegProcedure,
                           ObjectIdGetDatum(accessMethodObjectId));
    ScanKeyEntryInitialize(&entry[1],
                           0,
                           Anum_pg_amop_amopclaid,
                           ObjectIdEqualRegProcedure,
                           0);
    relation            = heap_openr(AccessMethodOperatorRelationName);
    operatorRelation    = heap_openr(OperatorRelationName);
    for(attributeNumber = maxAttributeNumber;
        attributeNumber > 0;
        attributeNumber--){
      StrategyNumber strategy;
      entry[1].sk_argument = ObjectIdGetDatum(operatorClassObjectId[attributeNumber -1]);
      map = IndexStrategyGetStrategyMap(indexStrategy,
                                        maxStrategyNumber,
                                        attributeNumber);
      for(strategy = 1;
          strategy <= maxStrategyNumber;
          strategy++)
        ScanKeyEntrySetIllegal(StrategyMapGetScanKeyEntry(map, strategy));

      scan = heap_beginscan(relation, false, NowTimeQual, 2, entry);
      while(tuple = heap_getnext(scan, 0, (Buffer *)NULL),
            HeapTupleIsValid(tuple)){
        Form_pg_amop form;
        form = (Form_pg_amop)GETSTRUCT(tuple);
        OperatorRelationFillScanKeyEntry(operatorRelation,
                                         form->amopopr,
                                         StrategyMapGetScanKeyEntry(map, form->amopstrategy));
      }
      heap_endscan(scan);
  }

    heap_close(operatorRelation);
    heap_close(relation);
}

Size
AttributeNumberGetIndexStrategySize(AttrNumber     maxAttributeNumber,
                                    StrategyNumber maxStrategyNumber){
  maxStrategyNumber = AMStrategies(maxStrategyNumber);
  return maxAttributeNumber * maxStrategyNumber * sizeof(ScanKeyData);
}

StrategyMap
IndexStrategyGetStrategyMap(IndexStrategy  indexStrategy,
                            StrategyNumber maxStrategyNum,
                            AttrNumber     attrNum){
  Assert(IndexStragegyIsValid(indexStrgegy));
  Assert(StragegyNumberIsValid(maxStrategyNum));
  Assert(AttributeNumberIsValid(attrNum));

  maxStrategyNum = AMStrategies(maxStrategyNum);
  return &indexStrategy->strategyMapData[maxStrategyNum * (attrNum -1)];
}

ScanKey
StrategyMapGetScanKeyEntry(StrategyMap     map,
                           StrategyNumber  strategyNumber){
  Assert(StrategyMapIsValid(map));
  Assert(StrategyNumberIsValid(strategyNumber));
  return (&map->entry[strategyNumber -1]);
}

static void
OperatorRelationFillScanKeyEntry(Relation operatorRelation,
                                 Oid      operatorObjectId,
                                 ScanKey  entry){
  HeapScanDesc    scan;
  ScanKeyData     scanKeyData;
  HeapTuple       tuple;

  ScanKeyEntryInitialize(&scanKeyData,
                         0,
                         ObjectIdAttributeNumber,
                         ObjectIdEqualRegProcedure,
                         ObjectIdGetDatum(operatorObjectId));
  scan = heap_beginscan(operatorRelation,
                        false,
                        NowTimeQual,
                        1,
                        &scanKeyData);
  tuple = heap_getnext(scan,
                       false,
                       (Buffer *)NULL);
  if(! HeapTupleIsValid(tuple)){
    elog(WARN, "OperatorObjectIdFillScanKeyEntry: unknown operator %lu",
         (uint32)operatorObjectId);
  }

  entry->sk_flags     = 0;
  entry->sk_procedure = ((OperatorTupleForm)GETSTRUCT(tuple))->oprcode;
  fmgr_info(entry->sk_procedure,
            &entry->sk_func,
            &entry->sk_nargs);

  if(! RegProcedureIsValid(entry->sk_procedure)){
    elog(WARN, "OperatorObjectIdFillScanKeyEntry: no procedure for operator %lu",
         (uint32) operatorObjectId);
  }
  heap_endscan(scan);
}
