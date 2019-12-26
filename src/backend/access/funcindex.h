#ifndef FUNCINDEX_H
#define FUNCINDEX_H
#include "postgres.h"

typedef struct {
  int      nargs;
  Oid      arglist[8];
  Oid      procOid;
  NameData funcName;
} FuncIndexInfo;

typedef FuncIndexInfo *FuncIndexInfoPtr;







#endif
