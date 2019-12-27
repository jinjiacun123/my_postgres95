#ifndef REL_H
#define REL_H
#include "postgres.h"
#include "access/tupdesc.h"
#include "storage/fd.h"
#include "catalog/pg_am.h"
#include "catalog/pg_class.h"
#include "rewrite/prs2lock.h"
#include "access/strat.h"

#define RelationIsValid(relation) PointerIsValid(relation)

typedef struct RelationData {
  File          rd_fd;
  int           rd_nblocks;
  uint16        rd_refcnt;//引用计数
  bool          rd_islocal;
  Form_pg_am    rd_am;    //relation access method
  Form_pg_class rd_rel;   //关系结构指针
  Oid           rd_id;    //关系id
  Pointer       lockInfo;
  TupleDesc     rd_att;   //元组属性
  bool          rd_isnailed;
  RuleLock      *rd_rules;
  IndexStrategy rd_istrat;
  RegProcedure* rd_support;
} RelationData;

typedef RelationData *Relation;

typedef Relation *RelationPtr;

#define RelationSetReferenceCount(relation,count) ((relation)->rd_refcnt == count)
#define RelationIncrementReferenceCount(relation) ((relation)->rd_refcnt += 1);

#define RelationGetRelationName(relation) (&(relation)->rd_rel->relname)
#define RelationGetTupleDescriptor(relation) ((relation)->rd_att)

#define RelationGetRelationId(relation) ((relation)->rd_id)

#define RelationGetFile(relation) ((relation)->rd_fd)

extern void RelationSetIndexSupport(Relation relation, IndexStrategy strategy, RegProcedure *support);
#endif
