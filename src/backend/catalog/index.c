#include "postgres.h"
#include "access/relscan.h"
#include "access/skey.h"
#include "utils/tqual.h"
#include "bootstrap/bootstrap.h"
#include "catalog/catname.h"
#include "catalog/pg_proc.h"

Form_pg_am
AccessMethodObjectIdGetAccessMethodTupleForm(Oid accessMethodObjectId){
  Relation     pg_am_desc;
  HeapScanDesc pg_am_scan;
  HeapTuple    pg_am_tuple;
  ScanKeyData  key;
  Form_pg_am   form;

  ScanKeyEntryInitialize(&key,
                         0,
                         ObjectIdAttributeNumber,
                         ObjectIdEqualRegProcedure,
                         ObjectIdGetDatum(accessMethodObjectId));
  pg_am_desc  = heap_openr(AccessMethodRelationName);
  pg_am_scan  = heap_beginscan(pg_am_desc, 0, NowTimeQual, 1, &key);
  pg_am_tuple = heap_getnext(pg_am_scan, 0, (Buffer *)NULL);

  if(! HeapTupleIsValid(pg_am_tuple)){
    heap_endscan(pg_am_scan);
    heap_close(pg_am_desc);
    return NULL;
  }

  form = (Form_pg_am)palloc(sizeof *form);
  memcpy(form, GETSTRUCT(pg_am_tuple), sizeof *form);

  heap_endscan(pg_am_scan);
  heap_close(pg_am_desc);
  return (form);
}
