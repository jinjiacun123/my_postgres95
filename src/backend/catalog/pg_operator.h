#ifndef OPERATOR_H
#define OPERATOR_H
#include "postgres.h"

CATALOG(pg_operator){
  NameData         oprname;
  Oid              oprowner;
  int2             oprprec;
  char             oprkind;
  bool             oprisleft;
  bool             oprcanhash;
  Oid              oprleft;
  Oid              oprright;
  Oid              oprresult;
  Oid              oprcom;
  Oid              oprnegate;
  Oid              oprlsortop;
  Oid              oprrsortop;
  regproc          oprcode;
  regproc          oprrest;
  regproc          oprjoin;
} FormData_pg_operator;

typedef FormData_pg_operator *OperatorTupleForm;

#endif
