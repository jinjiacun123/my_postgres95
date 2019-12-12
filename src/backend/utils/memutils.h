#ifndef MEMUTILS_H
#define MEMUTILS_H
#include "c.h"

typedef struct OrderedElemData OrderedElemData;
typedef OrderedElemData       *OrderedElem;

typedef struct OrderedSetData OrderedSetData;
typedef OrderedSetData        *OrderedSet;

struct OrderedElemData {
  OrderedElem next;
  OrderedElem prev;
  OrderedSet  set;
};

struct OrderedSetData{
  OrderedElem head;
  OrderedElem dumy;
  OrderedElem tail;
  Offset      offset;
};

typedef struct AllocSetData{
  OrderedSetData setData;
} AllocSetData;

typedef Pointer AllocPointer;

typedef AllocSetData *AllocSet;

extern void AllocPointerDump(AllocPointer pointer);
extern void AllocSetDump(AllocSet set);
#endif
