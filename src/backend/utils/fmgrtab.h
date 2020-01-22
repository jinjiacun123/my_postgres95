#ifndef FMGRTAB_H
#define FMGRTAB_H
#include "postgres.h"


typedef struct {
  Oid        proid;
  uint16     nargs;
  func_ptr   func;
  char*      funcName;
} FmgrCall;



extern FmgrCall *fmgr_isbuiltin(Oid id);


#endif
