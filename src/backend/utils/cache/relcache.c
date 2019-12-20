#include "access/tupdesc.h"
#include "access/heapam.h"
#include "access/htup.h"
#include "utils/elog.h"
#include "utils/mcxt.h"
#include "utils/rel.h"
#include "utils/hsearch.h"
#include "utils/relcache.h"
#include "utils/palloc.h"
#include "miscadmin.h"
#include "storage/smgr.h"

GlobalMemory CacheCxt;
static List *newlyCreatedRelns = NULL;

HTAB *RelationNameCache;
HTAB *RelationIdCache;

#define INFO_RELID   1
#define INFO_RELNAME 2
typedef struct RelationBuildDescInfo {
  int infotype;
  union {
    Oid info_id;
    char *info_name;
  } i;

} RelationBuildDescInfo;

static Relation RelationBuildDesc(RelationBuildDescInfo buildinfo);

typedef struct relidcacheent {
  Oid      reloid;
  Relation reldesc;
} RelIdCacheEnt;

typedef struct relnamecacheent {
  NameData relname;
  Relation reldesc;
} RelNameCacheEnt;

#define RelationCacheInsert(RELATION) \
  { RelIdCacheEnt *idhentry; RelNameCacheEnt *namehentry;\
  char *relname; Oid reloid;bool found;\
  relname = (RELATION->rd_rel->relname).data;\
  namehentry = (RelNameCacheEnt*)hash_search(RelationNameCache,    \
                                              relname,              \
                                              HASH_ENTER,           \
                                              &found);              \
  if(namehentry == NULL){                                               \
   elog(FATAL, "can't insert into relation desciptor cache");           \
  }                                                                     \
  if(found && !IsBootstrapProcessingMode()){                            \
    ;\
  }\
  namehentry->reldesc = RELATION;\
  reloid = RELATION->rd_id;\
  idhentry = (RelIdCacheEnt*)hash_search(RelationIdCache,\
                                         (char *)&reloid,\
                                         HASH_ENTER,\
                                         &found);\
  if(idhentry == NULL){                                         \
    elog(FATAL, "can't insert into relation descriptor cache"); \
  }                                                             \
  if(found && !IsBootstrapProcessingMode()){ \
                                            ;\
  }                                          \
  idhentry->reldesc = RELATION;\
  }


#define RelationNameCacheLookup(NAME, RELATION) \
  { RelNameCacheEnt *hentry; bool found;                              \
    hentry = (RelNameCacheEnt*)hash_search(RelationNameCache,         \
                                           (char *)NAME, HASH_FIND,   \
                                           &found);                   \
    if(hentry == NULL) {                                              \
      elog(FATAL, "error in CACHE");                                  \
    }                                                                 \
    if(found) {                                                       \
      RELATION = hentry->reldesc;                                     \
    } else {                                                          \
      RELATION = NULL;                                                \
    }                                                                 \
  }

void
RelationRegisterRelation(Relation relation){
  MemoryContext oldcxt;
  Relation      tmpRelation;
  char          tmpName[32] = "pg_proc";

  oldcxt = MemoryContextSwitchTo((MemoryContext)CacheCxt);
  if(oldcxt != (MemoryContext)CacheCxt)
    elog(NOIND, "RelationRegisterRelation:WARING: Context != CacheCxt");

  RelationCacheInsert(relation);
  RelationNameCacheLookup(tmpName, tmpRelation);

  RelationInitLockInfo(relation);

  relation->rd_islocal = TRUE;
  newlyCreatedRelns    = lcons(relation, newlyCreatedRelns);

  MemoryContextSwitchTo(oldcxt);
}

Relation
RelationNameGetRelation(char *relationName){
  Relation rd;
  RelationBuildDescInfo buildinfo;

  IncrHeapAccessStat(local_RelationNameGetRelation);
  IncrHeapAccessStat(global_RelationNameGetRelation);

  rd = RelationNameCacheGetRelation(relationName);
  if(RelationIsValid(rd))
    return (rd);

  buildinfo.infotype    = INFO_RELNAME;
  buildinfo.i.info_name = relationName;

  rd = RelationBuildDesc(buildinfo);
  return rd;
}

static Relation
RelationBuildDesc(RelationBuildDescInfo buildinfo){
  File               fd;
  Relation           relation;
  u_int              natts;
  Oid                relid;
  Oid                relam;
  Form_pg_class      relp;
  AttributeTupleForm attp = NULL;
  MemoryContext      oldcxt;
  HeapTuple          pg_class_tuple;

  oldcxt = MemoryContextSwitchTo((MemoryContext)CacheCxt);
  pg_class_tuple = ScanPgRelation(buildinfo);
  if(! HeapTupleIsValid(pg_class_tuple)){
    MemoryContextSwitchTo(oldcxt);
    return NULL;
  }

  relid    = pg_class_tuple->t_oid;
  relp     = (Form_pg_class)GETSTRUCT(pg_class_tuple);
  natts    = relp->relnatts;
  relation = AllocateRelationDesc(natts, relp);
  relam    = relation->rd_rel->relam;

  relation->rd_id = relid;
  RelationGetReferenceCount(relation, 1);
  relation->rd_isnailed = false;
  if(OidIsValid(relam)){
    relation->rd_am = (Form_pg_am)AccessMethodObjectIdGetAccessMethodTupleForm(relam);
  }
  RelationBuildTupleDesc(buildinfo ,relation, attp, natts);

  if(relp->relhasrules){
    RelationBuildRuleLock(relation);
  } else {
    relation->rd_rules = NULL;
  }

  if(OidIsValid(relam)){
    IndexedAccessmethodInitalize(relation);
  }

  RelationInitLockInfo(relation);

  fd = smgropen(relp->relsmgr, relation);
  Assert(fd >= -2);
  if(fd == -1)
    elog(NOTICE, "RelationIdBuildRelation: smgropen(%s): %m", &relp->relname);
  relation->rd_fd = fd;
  RelationCacheInsert(relation);
  pfree(pg_class_tuple);
  MemoryContextSwitchTo(oldcxt);
  return relation;
}
