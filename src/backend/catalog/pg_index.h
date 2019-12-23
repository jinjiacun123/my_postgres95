#ifndef PG_INDEX_H
#define PG_INDEX_H
#include "postgres.h"

CATALOG(pg_index) {
  Oid   indexrelid;
  Oid   indrelid;
  Oid   indproc;
  int28 indkey;
  oid8  indclass;
  bool  indisclustered;
  bool  indisarchived;
  text  indpred;
} FormData_pg_index;

typedef FormData_pg_index *IndexTupleForm;

#define Anum_pg_index_indexrelid 1

#endif
