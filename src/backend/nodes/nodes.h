#ifndef NODES_H
#define NODES_H
#include "c.h"


typedef enum NodeTag{
  T_Invalid = 0,

  T_MemoryContext = 400,
  T_GlobalMemory,

  T_Value = 500,
  T_List
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




#endif
