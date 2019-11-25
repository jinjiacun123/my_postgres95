#ifndef SKEY_H
#define SKEY_H
#include "postgres.h"
#include "access/attnum.h"

typedef struct ScanKeyData {
  bits16       sk_flags;
  AttrNumber   sk_attno;
  RegProcedure sk_procedure;
  func_ptr     sk_func;
  int32        sk_nargs;
  Datum        sk_argument;
} ScanKeyData;

#endif
