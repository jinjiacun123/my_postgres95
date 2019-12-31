#include "postgres.h"
#include "access/skey.h"
#include "access/attnum.h"

void
ScanKeyEntryInitialize(ScanKey      entry,
                       bits16       flags,
                       AttrNumber   attributeNumber,
                       RegProcedure procedure,
                       Datum        argument){
  Assert(PointerIsValid(entry));

  entry->sk_flags     = flags;
  entry->sk_attno     = attributeNumber;
  entry->sk_procedure = procedure;
  entry->sk_argument  = argument;
  fmgr_info(procedure, &entry->sk_func, &entry->sk_nargs);

  Assert(ScanKeyEntryIsLegal(entry));
}

void
ScanKeyEntrySetIllegal(ScanKey entry){
  Assert(PointerIsValid(entry));

  entry->sk_flags     = 0;
  entry->sk_attno     = InvalidAttrNumber;
  entry->sk_procedure = 0;
}
