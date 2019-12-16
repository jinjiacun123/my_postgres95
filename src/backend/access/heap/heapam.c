#include "utils/rel.h"
#include "utils/elog.h"
#include "access/heapam.h"

Relation
heap_openr(char *relationName){
  Relation r;

  IncrHeapAccessStat(local_openr);
  IncrHeapAccessStat(global_openr);
  r = RelationNameGetRelation(relationName);
  if(RelationIsValid(r) && r->rd_rel->relkind == RELKIND_INDEX){
    elog(WARN, "%s is an index relation", r->rd_rel->relname.data);
  }

  return r;
}
