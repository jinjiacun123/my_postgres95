#ifndef PG_AM_H
#define PG_AM_H
#include "postgres.h"

CATALOG(pg_am){
  NameData amname;
  Oid      amowner;
  char     amkind;
  int2     amstrategies;
  int2     amsupport;
  regproc  amgettuple;
  regproc  aminsert;
  regproc  amdelete;
  regproc  amgetattr;
  regproc  amsetlock;
  regproc  amsettid;
  regproc  amfreetuple;
  regproc  ambeginscan;
  regproc amrescan;
  regproc amendscan;
  regproc ammarkpost;
  regproc amrestrpos;
  regproc amopen;
  regproc amclose;
  regproc ambuild;
  regproc amcreate;
  regproc amdestroy;
}FormData_pg_am;

typedef FormData_pg_am *Form_pg_am;

#endif
