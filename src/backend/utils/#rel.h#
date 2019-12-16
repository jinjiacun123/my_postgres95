#ifndef REL_H
#define REL_H
#include "postgres.h"
#include "access/tupdesc.h"
#include "storage/fd.h"
#include "catalog/pg_class.h"

#define RelationIsValid(relation) PointerIsValid(relatio)

typedef struct RelationData {
  File          rd_fd;
  Form_pg_class rd_rel;//关系结构指针
  Oid           rd_id; //关系id
  TupleDesc     rd_att;//元组属性
  bool          rd_isnailed;
} RelationData;

typedef RelationData *Relation;

#endif
