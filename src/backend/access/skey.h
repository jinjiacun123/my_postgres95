#ifndef SKEY_H
#define SKEY_H
#include "postgres.h"
#include "access/attnum.h"

#define SK_ISNULL    0x1
#define SK_UNARY     0x2
#define SK_NEGATE    0x4
#define SK_COMMUTE   0x8

typedef struct ScanKeyData {
  bits16       sk_flags;
  AttrNumber   sk_attno;
  RegProcedure sk_procedure;
  func_ptr     sk_func;
  int32        sk_nargs;
  Datum        sk_argument;
} ScanKeyData;

typedef ScanKeyData* ScanKey;

extern void ScanKeyEntryInitialize(ScanKey      entry,
                                   bits16       flags,
                                   AttrNumber   attributeNumber,
                                   RegProcedure procedure,
                                   Datum        argument);
extern void ScanKeyEntrySetIllegal(ScanKey entry);

#endif
