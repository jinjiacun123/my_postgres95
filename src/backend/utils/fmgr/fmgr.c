#include <stdarg.h>
#include "postgres.h"
#include "utils/fmgrtab.h"
#include "access/htup.h"
#include "catalog/pg_proc.h"
#include "catalog/pg_language.h"
#include "utils/syscache.h"
#include "utils/elog.h"
#include "fmgr.h"

void
fmgr_info(Oid          procedureId,
          func_ptr     *function,
          int          *nargs){
  func_ptr              user_fn;
  FmgrCall              *fcp;
  HeapTuple             procedureTuple;
  FormData_pg_proc      *procedureStruct;
  Oid                   language;

  if(!(fcp = fmgr_isbuiltin(procedureId))){
    procedureTuple = SearchSysCacheTuple(PROOID,
                                         ObjectIdGetDatum(procedureId),
                                         0,
                                         0,
                                         0);
    if(!HeapTupleIsValid(procedureTuple)){
      elog(WARN, "fmgr_info: function %d: cache lookup failed\n", procedureId);
    }
    procedureStruct = (FormData_pg_proc *)GETSTRUCT(procedureTuple);
    if(!procedureStruct->proistrusted){
      *function = (func_ptr)NULL;
      *nargs    = procedureStruct->pronargs;
      return;
    }
    language = procedureStruct->prolang;
    switch(language){
    case INTERNALlanguageId:
      user_fn = fmgr_lookupByName(procedureStruct->proname.data);
      if(!user_fn)
        elog(WARN, "fmgr_info: function %s:: not in internal table",
             procedureStruct->proname.data);
      break;
    case ClanguageId:
      user_fn = fmgr_dynamic(procedureId, nargs);
      break;
    case SQLlanguageId:
      user_fn = (func_ptr)NULL;
      *nargs  = procedureStruct->pronargs;
      break;
    default:
      elog(WARN, "fmgr_info: function %d: unknown language %d",
           procedureId,
           language);
    }
  } else {
    user_fn  = fcp->func;
    *nargs   = fcp->nargs;
  }
  *function = user_fn;
}

char *
fmgr(Oid procedureId, ... ){
  va_list    pvar;
  register   i;
  int        pronargs;
  FmgrValues values;
  func_ptr   user_fn;
  bool       isNull = false;

  va_start(pvar, procedureId);

  fmgr_info(procedureId, &user_fn, &pronargs);

  if(pronargs > MAXFMGRARGS){
    elog(WARN, "fmgr: function %d: too many arguments (%d > %d)",
         procedureId,
         pronargs,
         MAXFMGRARGS);
  }
  for(i = 0; i< pronargs; ++i)
    values.data[i] = va_arg(pvar, char*);
  va_end(pvar);

  return(fmgr_c(user_fn,
                procedureId,
                pronargs,
                &values,
                &isNull));
}

char *
fmgr_c(func_ptr   user_fn,
       Oid        func_id,
       int        n_arguments,
       FmgrValues *values,
       bool       *isNull){
  char *returnValue = (char *)NULL;

  return(returnValue);
}
