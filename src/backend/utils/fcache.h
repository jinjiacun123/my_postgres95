#ifndef FCACHE_H
#define FCACHE_H

typedef struct {
  int      typlen;
  int      typbyval;
  func_ptr func;
  Oid      foid;
  Oid      language;
  int      nargs;
  Oid      *argOidVect;
  bool     *nullVect;
  char     *src;
  char     *bin;
  char     *func_state;

  bool     oneResult;
  bool     hasSetArg;
  Pointer  funcSlot;
  char     *setArg;
  bool     istrusted;
} FunctionCache, *FunctionCachePtr;

#endif
