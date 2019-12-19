#include "postgres.h"
#include "nodes/nodes.h"

Node *
newNode(Size size, NodeTag tag){
  Node *newNode;

  Assert(size >= 4);

  newNode = (Node *)palloc(size);
  memset((char *)newNode, 0, size);
  newNode->type = tag;
  return (newNode);
}
