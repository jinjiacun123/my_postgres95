#ifndef PG_TYPE_H
#define PG_TYPE_H
#include "postgres.h"

CATALOG(pg_type) BOOTSTRAP {
  NameData typname;
  Oid      typowner;
  int2     typlen;
  int2     typprtlen;
  bool     typbyval;
  char     typtype;
  bool     typisdefined;
  char     typdelim;
  Oid      typelem;
  regproc  typinput;
  regproc  typoutput;
  regproc  receive;
  regproc  typsend;
  char     typalign;
  text     typdefault;
} TypeTupleFormData;

#endif
