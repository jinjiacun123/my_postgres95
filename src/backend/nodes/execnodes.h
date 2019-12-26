#ifndef EXECNODES_H
#define EXECNODES_H
#include "access/sdir.h"
#include "access/funcindex.h"
#include "utils/rel.h"
#include "nodes/params.h"
#include "executor/tuptable.h"

typedef struct JunkFilter {
  NodeTag          type;
  List             *jf_targetList;
  int              jf_length;
  TupleDesc        jf_tupType;
  List             *jf_cleanTargetList;
  int              jf_cleanLength;
  TupleDesc        jf_cleanTupType;
  AttrNumber       *jf_cleanMap;
} JunkFilter;

typedef struct IndexInfo {
  NodeTag           type;
  int               ii_NumKeyAttributes;
  AttrNumber        *ii_KeyAttributeNumbers;
  FuncIndexInfoPtr  ii_FuncIndexInfo;
  Node              *ii_Predicate;
} IndexInfo;

typedef struct RelationInfo {
  NodeTag      type;
  Index        ri_RangeTableIndex;
  Relation     ri_RelationDesc;
  int          ri_NumIndeces;
  RelationPtr  ri_IndexRelationDescs;
  IndexInfo    **ri_IndexRelationInfo;
} RelationInfo;

typedef struct EState {
  NodeTag           type;
  ScanDirection     es_direction;
  List              *es_range_table;
  RelationInfo      *es_result_relation_info;
  Relation          es_into_relation_descriptor;
  ParamListInfo     es_param_list_info;
  int               es_BaseId;
  TupleTable        es_tupleTable;
  JunkFilter        *es_junkFilter;
  int               *es_refcount;
} EState;

typedef struct ExprContext {
  NodeTag           type;
  TupleTableSlot    *ecxt_scantuple;
  TupleTableSlot    *ecxt_innertuple;
  TupleTableSlot    *ecxt_outertuple;
  Relation          ecxt_relation;
  Index             ecxt_relid;
  ParamListInfo     ecxt_param_list_info;
  List              *ecxt_range_table;
  Datum             *ecxt_values;
  char              *ecxt_nulls;
} ExprContext;

typedef struct ProjectionInfo {
  NodeTag            type;
  List               *pi_targetlist;
  int                pl_len;
  Datum              *pi_tupValue;
  ExprContext        *pi_exprContext;
  TupleTableSlot     *pi_slot;
} ProjectionInfo;

typedef struct CommonState {
  NodeTag        type;
  int            cs_base_id;
  TupleTableSlot *cs_OuterTupleSlot;
  TupleTableSlot *cs_ResultTupleSlot;
  ExprContext    *cs_ExprContext;
  ProjectionInfo *cs_ProjInfo;
  bool           cs_TupFromTlist;
} CommonState;

typedef struct AppendState {
  CommonState cstate;
  int         as_whichplan;
  int         as_nplans;
  bool        *as_initialized;
  List        *as_rentries;
  List        *as_result_relation_info_list;
  List        *as_junkFilter_list;
} AppendState;

typedef CommonState JoinState;

typedef struct NestLoopState {
  JoinState jstate;
  bool      nl_PortalFlag;
} NestLoopState;

typedef struct HashJoinState {
  JoinState             jstate;
  HashJoinTable         hj_HashTable;
  IpcMemoryId           hj_HashTableShmId;
  HashBucket            hj_CurBucket;
  HeapTuple             hj_CurTuple;
  OverflowTuple         hj_CurOTuple;
  Var                   *hj_InnerHashKey;
  File                  *hj_OuterBatches;
  File                  *hj_InnerBatches;
  char                  *hj_OuterReadPos;
  int                   hj_OuterReadBlk;
  TupleTableSlot        *hj_OuterTupleSlot;
  TupleTableSlot        *hj_HashTupleSlot;
} HashJoinState;

typedef struct MergeJoinState {
  JoinState      jstate;
  List           *mj_QSortopI;
  List           *mj_ISortopO;
  int            mj_JoinState;
  TupleTableSlot *mj_MarkedTupleSlot;
} MergeJoinState;

typedef struct CommonScanState {
  CommonState         cstate;
  Relation            css_currentRelation;
  HeapScanDesc        css_currentScanDesc;
  TupleTableSlot      *css_ScanTupleSlot;
} CommonScanState;

typedef struct IndexScanState {
  CommonState       cstate;
  int               iss_NumIndices;
  int               iss_IndexPtr;
  ScanKey           *iss_ScanKey;
  int               *iss_NumScanKeys;
  Pointer           iss_RuntimeKeyInfo;
  RelationPtr       iss_RelationDescs;
  IndexScanDescPtr  iss_ScanDescs;
} IndexScanState;

typedef struct SortState {
  CommonScanState csstate;
  bool            sort_Flag;
  ScanKey         sort_keys;
  Relation        sort_TempRelation;
} SortState;

typedef struct AggState {
  CommonScanState csstate;
  bool            agg_done;
} AggState;

typedef CommonState UniqueState;

typedef struct HashState {
  CommonState cstate;
  File        *hashBatches;
} HashState;




#endif
