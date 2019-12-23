#ifndef PG_AMPROC_H
#define PG_AMPROC_H
#include "postgres.h"

CATALOG(){
  Oid  amid;
  Oid  amopclaid;
  Oid  amproc;
  int2 amprocnum;
} FormData_pg_amproc;

typedef FormData_pg_amproc *Form_pg_amproc;

#define Anum_pg_amproc_amid      1
#define Anum_pg_amproc_amopclaid 2

#endif
