#ifndef PLANNODES_H
#define PLANNODES_H
#include "nodes/primnodes.h"
#include "nodes/execnodes.h"
#include "nodes/nodes.h"
#include "storage/ipc.h"
#include "executor/hashjoin.h"

typedef struct Plan {
  NodeTag      type;
  Cost         cost;
  int          plan_size;
  int          plan_width;
  int          plan_tupperpage;
  EState       *state;

  List         *targetlist;
  List         *qual;
  struct Plan  *lefttree;
  struct Plan  *righttree;
} Plan;

typedef struct ResultState {
  CommonState   cstate;
  int           rs_done;
} ResultState;

typedef struct Result {
  Plan        plan;
  Node        *resconstantqual;
  ResultState *resstate;
} Result;

typedef Plan Existential;

typedef struct Append {
  Plan        plan;
 List        *unionplans;
  Index       unionrelid;
  List        *unionrtentries;
  AppendState *unionstate;
} Append;

typedef Plan Join;

typedef struct NestLoop {
  Join          join;
  NestLoopState *nlstate;
} NestLoop;

typedef struct MergeJoin {
  Join           join;
  List           *mergeclauses;
  Oid            mergesortop;
  Oid            *mergerightorder;
  Oid            *mergeleftorder;
  MergeJoinState *mergestate;
} MergeJoin;

typedef struct HashJoin {
  Join          join;
  List          *hashclauses;
  Oid           hashjoinop;
  HashJoinState *hashjoinstate;
  HashJoinTable hashjointable;
  IpcMemoryKey  hashjointablekey;
  int           hashjointablesize;
  bool          hashdone;
} HashJoin;

typedef struct Scan {
  Plan            plan;
  Index           scanrelid;
  CommonScanState *scanstate;
} Scan;

typedef Scan SeqScan;

typedef struct IndexScan {
  Scan            scan;
  List            *indxid;
  List            *indxqual;
  IndexScanState  *indxstate;
} IndexScan;

typedef struct Temp {
  Plan       plan;
  Oid        tempid;
  int        keycount;
} Temp;

typedef struct Sort {
  Plan      plan;
  Oid       tempid;
  int       keycount;
  SortState *sortstate;
} Sort;

typedef struct Agg {
  Plan     plan;
  int      numAgg;
  Aggreg   **aggs;
  AggState *aggstate;
} Agg;

typedef struct Unique {
  Plan           plan;
  Oid            tempid;
  int            keycount;
  char           *uniqueAttr;

  AttrNumber     uniqueAttrNum;

  UniqueState    *uniquestate;
} Unique;

typedef struct Var {
  NodeTag    type;
  Index      varno;
  AttrNumber varattno;
  Oid        vartype;
  Index      varnoold;
  AttrNumber varoattno;
} Var;

typedef struct Hash {
  Plan           plan;
  Var            *hashkey;
  HashState      *hashstate;
  HashJoinTable  hashtable;
  IpcMemoryKey   hashtablekey;
  int            hashtablesize;
} Hash;

#endif
