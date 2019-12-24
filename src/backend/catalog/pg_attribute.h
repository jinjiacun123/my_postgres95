#ifndef PG_ATTRIBUTE_H
#define PG_ATTRIBUTE_H
#include "postgres.h"

#define Natts_pg_attribute            16
#define Anum_pg_attribute_attrelid    1
#define Anum_pg_attribute_attname     2
#define Anum_pg_attribute_atttypeid   3
#define Anum_pg_attribute_attdefrel   4
#define Anum_pg_attribute_attnvals    5
#define Anum_pg_attribute_atttyparg   6
#define Anum_pg_attribute_attlen      7
#define Anum_pg_attribute_attnum      8
#define Anum_pg_attribute_attbound    9
#define Anum_pg_attribute_attbyval    10
#define Anum_pg_attribute_attcanindex 11
#define Anum_pg_attribute_attproc     12
#define Anum_pg_attribute_attrelems   13
#define Anum_pg_attribute_attcacheoff 14
#define Anum_pg_attribute_attisset    15
#define Anum_pg_attribute_attalign    16

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
