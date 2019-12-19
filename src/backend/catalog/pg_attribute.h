#ifndef PG_ATTRIBUTE_H
#define PG_ATTRIBUTE_H
#include "postgres.h"

CATALOG(pg_attribute) BOOTSTRAP {
  Oid      attrelid;
  NameData attname;
  Oid      atttypeid;
  Oid      attdefrel;
  int4     attnvals;
  Oid      atttypearg;
  int2     attlen;
  int2     attnum;
  int2     attbound;
  bool     attbyval;
  bool     attcanindex;
  Oid      attproc;
  int4     attnelems;
  int4     attcacheoff;
  bool     attisset;
  char     attalign;
} FormData_pg_attribute;


typedef FormData_pg_attribute *AttributeTupleForm;

#define ATTRIBUTE_TUPLE_SIZE \
  (offsetof(FormData_pg_attribute, attalign) + sizeof(char))

#endif
