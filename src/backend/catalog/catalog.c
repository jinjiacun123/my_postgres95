#include "postgres.h"
#include "miscadmin.h"
#include "catalog/catalog.h"
#include "catalog/catname.h"
#include "utils/elog.h"

Oid
newoid(){
  Oid lastoid;

  GetNewObjectId(&lastoid);
  if(! OidIsValid(lastoid))
    elog(WARN, "newoid: GetNewObjectId returns invalid oid");
  return lastoid;
}

bool
IsSharedSystemRelationName(char *relname){
  int i;

  if(!IsSystemRelationName(relname))
    return FALSE;

  i = 0;
  while( SharedSystemRelationNames[i] != NULL){
    if(strcmp(SharedSystemRelationNames[i], relname) == 0)
      return TRUE;
    i++;
  }
  return FALSE;
}

char *
relpath(char *relname[]){
  char *path;

  if(IsSharedSystemRelationName(relname)){
    path = (char *)palloc(strlen(DataDir) + sizeof(NameData) + 2);
    sprintf(path, "%s/%.*s", DataDir, NAMEDATALEN, relname);
    return(path);
  }

  return(relname);
}
