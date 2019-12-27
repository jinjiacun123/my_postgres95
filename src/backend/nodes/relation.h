#ifndef RELATION_H
#define RELATION_H
#include "postgres.h"
#include "nodes/pg_list.h"
#include "nodes/plannodes.h"
#include "nodes/primnodes.h"

typedef List *Relid;

typedef struct Iter{
  NodeTag type;
  Node    *iterexpr;
  Oid     itertype;
} Iter;

typedef struct JoinMethod {
  NodeTag type;
  List    *jmkeys;
  List    *clauses;
} JoinMethod;

typedef struct HInfo{
  JoinMethod jmethod;
  Oid        hashop;
} HInfo;

typedef struct JInfo {
  NodeTag type;
  List    *otherrels;
  List    *jinfoclauseinfo;
  bool    mergesortable;
  bool    hashjoinable;
  bool    inactive;
} JInfo;

typedef struct Rel {
  NodeTag          type;
  Relid            relids;
  bool             indexed;
  int              pages;
  int              tuples;
  int              size;
  int              width;

  List             *targetlist;
  List             *pathlist;
  struct Path      *unorderedpath;
  struct Path      *cheapestpath;
  bool             pruneable;
  Oid              *classlist;
  int              *indexkeys;
  Oid              relam;
  Oid              indproc;
  List             *indpred;
  Oid              *ordering;
  List             *clauseinfo;
  List             *joininfo;
  List             *innerjoin;
  List             *superrels;
} Rel;

typedef struct OrderKey {
  NodeTag    type;
  int        attribute_number;
  Index      array_index;
} OrderKey;

typedef struct JoinKey {
  NodeTag    type;
  Var        *outer;
  Var        *inner;
} JoinKey;

typedef struct MergeOrder {
  NodeTag   type;
  Oid       join_operator;
  Oid       left_operator;
  Oid       right_operator;
  Oid       left_type;
  Oid       right_type;
} MergeOrder;

typedef enum OrderType {
  MERGE_ORDER, SORTOP_ORDER
} OrderType;

typedef struct PathOrder {
  OrderType      ordtype;
  union {
    Oid         *sortop;
    MergeOrder  *merge;
  } ord;

} PathOrder;

typedef struct Path {
  NodeTag   type;
  Rel       *parent;
  Cost      path_cost;
  NodeTag   pathtype;
  PathOrder p_ordering;
  List      *keys;
  Cost      outerjoincost;
  Relid     joinid;
  List      *locclauseinfo;
} Path;

typedef struct JoinPath {
  Path      path;
  List      *pathclauseinfo;
  Path      *outerjoinpath;
  Path      *innerjoinpath;
} JoinPath;

typedef struct HashPath {
  JoinPath      jpath;
  List          *path_hashclauses;
  List          *outerhashkeys;
  List          *innerhashkeys;
} HashPath;

typedef struct IndexPath {
  Path    path;
  List    *indexid;
  List    *indexqual;
} IndexPath;



typedef struct MergePath {
  JoinPath     jpath;
  List         *path_mergeclauses;
  List         *outersortkeys;
  List         *innersortkeys;
} MergePath;

typedef struct CInfo {
  NodeTag    type;
  Expr       *clause;
  Cost       selectivity;
  bool       notclause;
  List       *indexids;
  MergeOrder *mergesortorder;
  Oid        hashjoinoperator;
  Relid      cinfojoinid;
} CInfo;



#endif
