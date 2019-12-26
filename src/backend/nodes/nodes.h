#ifndef NODES_H
#define NODES_H
#include "c.h"

typedef float Cost;

typedef enum NodeTag{
  T_Invalid = 0,

  T_Plan = 10,
  T_Existential,
  T_Result,
  T_Append,
  T_Scan,
  T_SeqScan,
  T_IndexScan,
  T_Join,
  T_NestLoop,
  T_MergeJoin,
  T_HashJoin,
  T_Temp,
  T_Material,
  T_Sort,
  T_Agg,
  T_Unique,
  T_Hash,

  T_Resdom = 100,
  T_Fjoin,
  T_Expr,
  T_Var,
  T_Oper,
  T_Const,
  T_Param,
  T_Aggreg,
  T_Func,
  T_Array,
  T_ArrayRef,

  T_Rel = 200,
  T_Path,
  T_IndexPath,
  T_JoinPath,
  T_MergePath,
  T_HashPath,
  T_OrderKey,
  T_JoinKey,
  T_MergeOrder,
  T_CInfo,
  T_JoinMethod,
  T_HInfo,
  T_MInfo,
  T_JInfo,
  T_Iter,
  T_Stream,

  T_IndexInfo = 300,
  T_RelationInfo,
  T_TupleCount,
  T_TupleTableSlot,
  T_ExprContext,
  T_projectionInfo,
  T_JunkFilter,
  T_EState,

  T_MemoryContext = 400,
  T_GlobalMemory,

  T_Value = 500,
  T_List,
  T_Integer,
  T_Float,
  T_String,
  T_Null,
  T_Query = 600,
  T_AppendStmt,
  T_DeleteStmt,
  T_ReplaceStmt,
  T_CursorStmt,
  T_RetrieveStmt,
  T_AddAttrStmt,
  T_AggregateStmt,
  T_ChangeACLStmt,
  T_ClosePortalStmt,
  T_ClusterStmt,
  T_CopyStmt,
  T_CreateStmt,
  T_VersionStmt,
  T_DefineStmt,
  T_DestroyStmt,
  T_ExtendStmt,
  T_FetchStmt,
  T_IndexStmt,
  T_MoveStmt,
  T_ProcedureStmt,
  T_PurgeStmt,
  T_RecipeStmt,
  T_RemoveFuncStmt,
  T_RemoveOperStmt,
  T_RemoveStmt,
  T_RenameStmt,
  T_RuleStmt,
  T_NotifyStmt,
  T_ListenStmt,
  T_TransactionStmt,
  T_ViewStmt,
  T_LoadStmt,
  T_CreatedStmt,
  T_DestroydbStmt,
  T_VecuumStmt,
  T_ExplainStmt,

  T_A_Expr = 700,
  T_Attr,
  T_A_Const,
  T_ParamNo,
  T_Ident,
  T_FuncCall,
  T_A_Indices,
  T_ResTarget,
  T_ParamString,
  T_TimeRange,
  T_RelExpr,
  T_SortBy,
  T_RangeVar,
  T_TypeName,
  T_IndexElem,
  T_ColumnDef,
  T_DefElem,
  T_TargetEntry,
  T_RangeTblEntry,
  T_SortClause,
  T_GroupClause
} NodeTag;

#define makeNode(_node_) (_node_*)newNode(sizeof(_node_), T_##_node_)

typedef struct Node {
  NodeTag type;
} Node;

extern Node *newNode(Size size, NodeTag tag);

typedef enum CmdType {
  CMD_UNKNOWN,
  CMD_SELECT,
  CMD_UPDATE,
  CMD_INSERT,
  CMD_DELETE,
  CMD_NOTIFY,
  CMD_UTILITY
} CmdType;

extern void *stringToNode(char *str);


#endif
