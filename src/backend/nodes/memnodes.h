#ifndef MEMNODES_H
#define MEMNODES_H
#include "c.h"
#include "utils/memutils.h"
#include "nodes/nodes.h"

typedef struct MemoryContextMethodsData{
  Pointer (*alloc)();
  void    (*free_p)();
  Pointer (*realloc)();
  char*   (*getName)();
  void    (*dump)();
} *MemoryContextMethods;

typedef struct MemoryContext{
  NodeTag              type;
  MemoryContextMethods method;
} *MemoryContext;

typedef struct GlobalMemory{
  NodeTag              type;
  MemoryContextMethods method;
  AllocSetData         setData;
  char                 *name;
  OrderedElemData      elemData;
} *GlobalMemory;

#endif
