#include "postgres.h"
#include "catalog/catalog.h"
#include "utils/elog.h"

Oid
newoid(){
  Oid lastoid;

  GetNewObjectId(&lastoid);
  if(! OidIsValid(lastoid))
    elog(WARN, "newoid: GetNewObjectId returns invalid oid");
  return lastoid;
}
