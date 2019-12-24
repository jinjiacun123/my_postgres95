#ifndef NODES_H
#define NODES_H
#include "c.h"


typedef enum NodeTag{
  T_Invalid = 0,

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

  T_MemoryContext = 400,
  T_GlobalMemory,

  T_Value = 500,
  T_List,
  T_Integer,
  T_Float,
  T_String,
  T_Null
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
