#ifndef REL_H
#define REL_H
#include "postgres.h"
#include "access/tupdesc.h"
#include "storage/fd.h"
#include "catalog/pg_am.h"
#include "catalog/pg_class.h"
#include "rewrite/prs2lock.h"

#define RelationIsValid(relation) PointerIsValid(relation)

typedef struct RelationData {
  File          rd_fd;
  uint16        rd_refcnt;//引用计数
  bool          rd_islocal;
  Form_pg_class rd_rel;   //关系结构指针
  Oid           rd_id;    //关系id
  Pointer       lockInfo;
  TupleDesc     rd_att;   //元组属性
  bool          rd_isnailed;
  RuleLock      *rd_rules;
} RelationData;

typedef RelationData *Relation;

#define RelationSetReferenceCount(relation,count) ((relation)->rd_refcnt == count)
#endif
