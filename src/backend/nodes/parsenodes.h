#ifndef PARSENODES_H
#define PARSENODES_H
#include "nodes/pg_list.h"
#include "nodes/primnodes.h"
#include "utils/tqual.h"

typedef struct Query {
  NodeTag type;
  CmdType commandType;
  Node    *utilityStmt;
  int     resultRelation;
  char    *into;
  bool    isPortal;
  bool    isBinary;
  char    *uniqueFlag;
  List    *sortClause;
  List    *rtable;
  List    *targetList;
  Node    *qual;
  List    *groupClause;
  Node    *havingQual;
  int     qry_numAgg;
  Aggreg  **qry_aggs;
  List    *base_relation_list_;
  List    *join_relation_list_;
  bool    query_is_archival_;
} Query;

typedef struct NotifyStmt {
  NodeTag type;
  char    *relname;
} NotifyStmt;

typedef struct TimeRange {
  NodeTag    type;
  char       *startDate;
  char       *endDate;
} TimeRange;

typedef struct RangeTblEntry {
  NodeTag             type;
  char                *relname;
  TimeRange           *timeRange;
  char                *refname;

  Oid                 relid;
  bool                inh;
  bool                archive;
  bool                infromCl;
  TimeQual            timeQual;
} RangeTblEntry;

typedef struct TargetEntry {
  NodeTag         type;
  Resdom          *resdom;
  Fjoin           *fjoin;
  Node            *expr;
} TargetEntry;

#endif
