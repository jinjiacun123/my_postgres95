#ifndef MEMUTILS_H
#define MEMUTILS_H
#include "c.h"

#define AllocPointerIsValid(pointer) PointerIsValid(pointer)

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

#define SHORTALIGN(LEN)\
  (((long)(LEN) + (sizeof(short) -1)) & ~(sizeof(short) -1))

#define INTALIGN(LEN)\
  (((long)(LEN) + (sizeof(int) -1)) & !(sizeof(int) -1))

#define LONGALIGN(LEN)\
  (((long)(LEN) + (sizeof(long) -1)) & !(sizeof(long) -1))

#define DOUBLEALIGN(LEN)\
  (((long)(LEN) + (sizeof(double)-1)) & ~(sizeof(double) -1))

#define MAXALIGN(LEN)\
  (((long)(LEN) + (sizeof(double) -1)) & ~(sizeof(double) -1))

extern void AllocPointerDump(AllocPointer pointer);
extern void AllocSetDump(AllocSet set);
extern Pointer OrderedSetGetHead(OrderedSet set);
extern AllocPointer AllocSetRealloc(AllocSet set,
                                    AllocPointer pointer,
                                    Size size);
#endif
