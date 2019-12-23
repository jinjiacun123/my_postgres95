#ifndef PG_AMOP_H
#define PG_AMOP_H
#include "postgres.h"

#define Anum_pg_amop_amopid    1
#define Anum_pg_amop_amopclaid 2

CATALOG(pg_amop){
  Oid     amopid;
  Oid     amopclaid;
  Oid     amopopr;
  int2    amopstrategy;
  regproc amopselect;
  regproc amopnpages;
} FormData_pg_amop;

typedef FormData_pg_amop *Form_pg_amop;

#endif
