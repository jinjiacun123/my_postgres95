#include "postgres.h"
#include "utils/rel.h"
#include "storage/lmgr.h"
#include "catalog/catname.h"
#include "catalog/pg_class.h"

Relation
heap_creatr(char      *name,
            unsigned  smgr,
            TupleDesc tupDesc)
{
  register unsigned i;
  Oid               relid;
  Relation          rdesc;
  int               len;
  bool              nailme  = false;
  int               natts   = tupDesc->natts;
  char*             relname = name;
  char              tempname[40];
  int               isTemp = 0;

  extern GlobalMemory CacheCxt;
  MemoryContext       oldcxt;

  AssertArg(natts > 0);

  if(!CacheCxt)
    CacheCxt = CreateGlobalMemory("Cache");

  oldcxt = MemoryContextSwitchTo((MemoryContext)CacheCxt);

  if(! strcmp(RelationRelationName, relname)){
    relid = RelOid_pg_class;
    nailme = true;
  } else if(! strcmp(AttributeRelationName, relname)){
    relid = RelOid_pg_attribute;
    nailme = true;
  } else if(! strcmp(ProcedureRelationName, relname)){
    relid = RelOid_pg_proc;
    nailme = true;
  } else if(! strcmp(TypeRelationName, relname)){
    relid = RelOid_pg_type;
    nailme = true;
  } else {
    relid = newoid();

    if(name[0] == '\0'){
      sprintf(tempname, "temp_%d", relid);
      relname = tempname;
      isTemp = 1;
    }
  }

  len = sizeof(RelationData);

  rdesc = (Relation) palloc(len);
  memset((char *)rdesc, 0, len);

  rdesc->rd_att = CreateTupleDescCopy(tupDesc);

  if(nailme)
    rdesc->rd_isnailed = true;

  RelationSetReferenceCount(rdesc, 1);

  rdesc->rd_rel = (Form_pg_class)palloc(sizeof * rdesc->rd_rel);
  memset((char *)rdesc->rd_rel, 0, sizeof *rdesc->rd_rel);
  namestrcpy(&(rdesc->rd_rel->relname), relname);
  rdesc->rd_rel->relkind  = RELKIND_UNCATALOGED;
  rdesc->rd_rel->relnatts = natts;
  rdesc->rd_rel->relsmgr  = smgr;

  for(i = 0; i < natts; i++){
    rdesc->rd_att->attrs[i]->attrelid = relid;
  }

  rdesc->rd_id = relid;

  if(nailme){
    rdesc->rd_rel->reltype = relid;
  }

  rdesc->rd_fd = (File)smgrcreate(smgr, rdesc);
  RelationRegisterRelation(rdesc);
  MemoryContextSwitchTo(oldcxt);

  if(isTemp)
    AddToTempRelList(rdesc);

  return (rdesc);
}
