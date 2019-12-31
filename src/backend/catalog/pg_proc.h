#ifndef PG_PROC_H
#define PG_PROC_H
#include "postgres.h"

CATALOG(pg_proc) BOOTSTRAP {
  NameData          proname;
  Oid               proowner;
  Oid               prolang;
  bool              proisinh;
  bool              proistrusted;
  bool              proiscacheable;
  int2              pronargs;
  bool              proretset;
  Oid               prorettype;
  oid8              proargtypes;

  int4              properbyte_cpu;
  int4              propercall_cpu;
  int4              prooutin_ratio;
  text              prosrc;
  bytea             probin;
} FormData_pg_proc;

typedef FormData_pg_proc  *Form_pg_proc;


#define ObjectIdEqualRegProcedure    184
#define Character16EqualRegProcedure 490
DATA(insert OID = 28 ( boolin  PGUID 11 f t f 1 f 16 "0" 100 0 0 100 foo bar));
DATA(insert OID = 29 ( boolout PGUID 11 f t f 1 f 23 "0" 100 0 0 100 foo bar));
DATA(insert OID = 47 ( textout PGUID 11 f t f 1 f 23 "0" 100 0 0 100 foo bar));
#endif
