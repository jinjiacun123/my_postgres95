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
#include "access/strat.h"
#include "utils/palloc.h"
#include "catalog/pg_rewrite.h"
#include "catalog/pg_class.h"
#include "catalog/catname.h"
#include "catalog/pg_proc.h"
#include "rewrite/prs2lock.h"
#include "storage/buf.h"
#include "utils/tqual.h"
#include "access/relscan.h"
#include "miscadmin.h"

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
static void     IndexedAccessMethodInitialize(Relation relation);
static void     RelationBuildRuleLock(Relation relation);
static void     RelationBuildTupleDesc(RelationBuildDescInfo buildinfo,
                                       Relation              relation,
                                       AttributeTupleForm    attp,
                                       u_int                 natts);
static Relation  AllocateRelationDesc(u_int natts, Form_pg_class relp);
static HeapTuple ScanPgRelation(RelationBuildDescInfo buildinfo);
static HeapTuple scan_pg_rel_seq(RelationBuildDescInfo buildinfo);
static void      build_tupdesc_seq(RelationBuildDescInfo buildinfo,
                                   Relation              relation,
                                   AttributeTupleForm    attp,
                                   u_int                 natts);

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

 static void IndexedAccessMethodInitialize(Relation relation);

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
     IndexedAccessMethodInitalize(relation);
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

 static void
 IndexedAccessMethodInitialize(Relation relation){
   IndexStrategy strategy;
   RegProcedure  *support;
   int           natts;
   Size          stratSize;
   Size          supportSize;
   uint16        relamstrategies;
   uint16        relamsupport;

   natts           = relation->rd_rel->relnatts;
   relamstrategies = relation->rd_am->amstrategies;
   stratSize       = AttributeNumberGetIndexStrategySize(natts, relamstrategies);
   strategy        = (IndexStrategy) palloc(stratSize);
   relamsupport    = relation->rd_am->amsupport;

   if(relamsupport > 0){
     supportSize = natts * (relamsupport * sizeof(RegProcedure));
     support     = (RegProcedure *) palloc(supportSize);
   } else {
     support = (RegProcedure *) NULL;
   }

   IndexSupportInitialize(strategy,
                          support,
                          relation->rd_att->attrs[0]->attrelid,
                          relation->rd_rel->relam,
                          relamstrategies,
                          relamsupport,
                          natts);
   RelationSetIndexSupport(relation, strategy, support);
 }

 static void
 RelationBuildRuleLock(Relation relation){
   HeapTuple    pg_rewrite_tuple;
   Relation     pg_rewrite_desc;
   TupleDesc    pg_rewrite_tupdesc;
   HeapScanDesc pg_rewrite_scan;
   ScanKeyData  key;
   RuleLock     *rulelock;
   int          numlocks;
   RewriteRule  **rules;
   int          maxlocks;

   maxlocks = 4;
   rules    = (RewriteRule **)palloc(sizeof(RewriteRule*) * maxlocks);
   numlocks = 0;

   ScanKeyEntryInitialize(&key,
                          0,
                          Anum_pg_rewrite_ev_class,
                          ObjectIdEqualRegProcedure,
                          ObjectIdGetDatum(relation->rd_id));
   pg_rewrite_desc = heap_openr(RewriteRelationName);
   pg_rewrite_scan = heap_beginscan(pg_rewrite_desc,
                                    0,
                                    NowTimeQual,
                                    1,
                                    &key);
   pg_rewrite_tupdesc = RelationGetTupleDescriptor(pg_rewrite_desc);
   while(pg_rewrite_tuple = heap_getnext(pg_rewrite_scan, 0, (Buffer *)NULL)){
     bool        isnull;
     char        *ruleaction = NULL;
     char        *rule_evqual_string;
     RewriteRule *rule;

     rule = (RewriteRule *)palloc(sizeof(RewriteRule));
     rule->ruleId = pg_rewrite_tuple->t_oid;
     rule->event =  (CmdType)((char)heap_getattr(pg_rewrite_tuple,
                         InvalidBuffer,
                         Anum_pg_rewrite_ev_type,
                         pg_rewrite_tupdesc,
                         &isnull)-48);
     rule->attrno = (AttrNumber)heap_getattr(pg_rewrite_tuple,
                                             InvalidBuffer,
                                             Anum_pg_rewrite_ev_attr,
                                             pg_rewrite_tupdesc,
                                             &isnull);
     ruleaction = heap_getattr(pg_rewrite_tuple,
                               InvalidBuffer,
                               Anum_pg_rewrite_action,
                               pg_rewrite_tupdesc,
                               &isnull);
     rule_evqual_string = heap_getattr(pg_rewrite_tuple,
                                       InvalidBuffer,
                                       Anum_pg_rewrite_ev_qual,
                                       pg_rewrite_tupdesc,
                                       &isnull);
     ruleaction = textout((struct varlena *)ruleaction);
     rule_evqual_string = textout((struct varlena *)rule_evqual_string);
     rule->actions = (List*)stringToNode(ruleaction);
     rule->qual = (Node*)stringToNode(rule_evqual_string);

     rules[numlocks++] = rule;
     if(numlocks == maxlocks){
       maxlocks *= 2;
       rules = (RewriteRule **)repalloc(rules, sizeof(RewriteRule) * maxlocks);
     }
   }
   heap_endscan(pg_rewrite_scan);
   heap_close(pg_rewrite_desc);
   rulelock = (RuleLock *)palloc(sizeof(RuleLock));
   rulelock->numLocks = numlocks;
   rulelock->rules    = rules;

   relation->rd_rules = rulelock;
   return;
 }

 static void
 RelationBuildTupleDsec(RelationBuildDescInfo buildinfo,
                        Relation              relation,
                        AttributeTupleForm    attp,
                        u_int                 natts){
   if(IsBootstrapProcessingMode())
     build_tupdesc_seq(buildinfo, relation, attp, natts);
 }

 static Relation
 AllocateRelationDesc(u_int natts, Form_pg_class relp){
   Relation      relation;
   Size          len;
   Form_pg_class relationTupleForm;

   relationTupleForm = (Form_pg_class)palloc(sizeof(FormData_pg_class));
   memmove((char *)relationTupleForm, (char *)relp, CLASS_TUPLE_SIZE);
   len = sizeof(RelationData) + 10;
   relation = (Relation) palloc(len);
   memset((char *)relation, 0, len);
   relation->rd_att = CreateTemplateTupleDesc(natts);
   relation->rd_rel = relationTupleForm;
   return relation;
 }

 static HeapTuple
 ScanPgRelation(RelationBuildDescInfo buildinfo){
   if(IsBootstrapProcessingMode())
     return (scan_pg_rel_seq(buildinfo));
 }

 Relation
 RelationNameCacheGetRelation(char *relationName){
   Relation rd;
   NameData name;

   memset(&name, 0, NAMEDATALEN);
   namestrcpy(&name, relationName);
   RelationNameCacheLookup(name.data, rd);

   if(RelationIsValid(rd)){
     if(rd->rd_fd == -1){
       rd->rd_fd = smgropen(rd->rd_rel->relsmgr, rd);
       Assert(rd->rd_fd != -1);
     }

     RelationIncrementReferenceCount(rd);
     RelationSetLockForDescriptorOpen(rd);
   }

   return (rd);
 }

 static HeapTuple
 scan_pg_rel_seq(RelationBuildDescInfo buildinfo){
   HeapTuple    pg_class_tuple;
   HeapTuple    return_tuple;
   Relation     pg_class_desc;
   HeapScanDesc pg_class_scan;
   ScanKeyData  key;
   Buffer       buf;

   switch(buildinfo.infotype){
   case INFO_RELID:
     ScanKeyEntryInitialize(&key,
                            0,
                            ObjectIdAttributeNumber,
                            ObjectIdEqualRegProcedure,
                            ObjectIdGetDatum(buildinfo.i.info_id));
     break;
   case INFO_RELNAME:
   ScanKeyEntryInitialize(&key,
                          0,
                          Anum_pg_class_relname,
                          Character16EqualRegProcedure,
                          NameGetDatum(buildinfo.i.info_name));
   break;
   default:
     elog(WARN, "ScanPgRelation: bad buildinfo");
   return NULL;
  }
   pg_class_desc = heap_openr(RelationRelationName);
   if(!IsInitProcessingMode())
     RelationSetLockForRead(pg_class_desc);
   pg_class_scan = heap_beginscan(pg_class_desc,
                                  0,
                                  NowTimeQual,
                                  1,
                                  &key);
   pg_class_tuple = heap_getnext(pg_class_scan, 0, &buf);

   if(! HeapTupleIsValid(pg_class_tuple)){
     return_tuple = pg_class_tuple;
   } else {
     return_tuple = (HeapTuple) palloc((Size) pg_class_tuple->t_len);
     memmove((char *)return_tuple,
             (char *) pg_class_tuple,
             (int) pg_class_tuple->t_len);
     ReleaseBuffer(buf);
   }

   heap_endscan(pg_class_scan);
   if(!IsInitProcessingMode())
     RelationUnsetLockForRead(pg_class_desc);
   heap_close(pg_class_desc);

   return return_tuple;
}

static void
build_tupdesc_seq(RelationBuildDescInfo buildinfo,
                  Relation            relation,
                  AttributeTupleForm  attp,
                  u_int               natts){
  HeapTuple    pg_attribute_tuple;
  Relation     pg_attribute_desc;
  HeapScanDesc pg_attribute_scan;
  ScanKeyData  key;
  int          need;

  ScanKeyEntryInitialize(&key,
                         0,
                         Anum_pg_attribute_attrelid,
                         ObjectIdEqualRegProcedure,
                         ObjectIdGetDatum(relation->rd_id));
  pg_attribute_desc = heap_openr(AttributeRelationName);
  pg_attribute_scan = heap_beginscan(pg_attribute_desc,
                                     0,
                                     NowTimeQual,
                                     1,
                                     &key);
  need = natts;
  pg_attribute_tuple = heap_getnext(pg_attribute_scan,
                                    0,
                                    (Buffer *)NULL);
  while(HeapTupleIsValid(pg_attribute_tuple) && need > 0 ){
    attp = (AttributeTupleForm) GETSTRUCT(pg_attribute_tuple);
    if(attp->attnum > 0){
      relation->rd_att->attrs[attp->attnum -1] = (AttributeTupleForm)palloc(ATTRIBUTE_TUPLE_SIZE);
      memmove((char *)(relation->rd_att->attrs[attp->attnum -1]), (char *)attp, ATTRIBUTE_TUPLE_SIZE);
      need--;
    }
    pg_attribute_tuple = heap_getnext(pg_attribute_scan,
                                      0,
                                      (Buffer *)NULL);
  }

  if(need > 0)
    elog(WARN, "catalog is missing %d attribute %s for relid %d",
         need,
         (need == 1 ? "":"s"),
         relation->rd_id);

  heap_endscan(pg_attribute_scan);
  heap_close(pg_attribute_desc);
}
