#include "utils/memutils.h"
#include "utils/elog.h"

typedef struct AllocElemData {
  OrderedElemData elemData;
  Size            size;
} AllocElemData;
typedef AllocElemData *AllocElem;
#define AllocPointerGetAllocElem(pointer) (&((AllocElem)(pointer))[-1])
#define AllocElemGetAllocPointer(alloc) ((AllocPointer)&(alloc)[1])

static AllocPointer AllocSetGetFirst(AllocSet set);
static AllocPointer AllocPointerGetNext(AllocPointer pointer);

AllocPointer
AllocSetAlloc(AllocSet set, Size size){
  AllocElem alloc;

  AssertArg(AllocSetIsValid(set));

  alloc = (AllocElem)malloc(sizeof (*alloc) + size);

  if(!PointerIsValid(alloc)){
    elog(FATAL, "palloc failture:memory exhauseted");
  }

  OrderedElemPushInto(&alloc->elemData, &set->setData);
  alloc->size = size;

  return (AllocElemGetAllocPointer(alloc));
}

void
AllocSetFree(AllocSet set, AllocPointer pointer){
  AllocElem alloc;

  AssertArg(AllocSetContain(set, pointer));



}

bool
AllocSetContains(AllocSet set, AllocPointer pointer)
{
  AssertArg(AllocSetIsValid(set));
  AssertArg(AllocPointerIsValid(pointer));

  return (OrderedSetContains(&set->setData, &AllocPointerGetAllocElem(pointer)->elemData));
}

void
AllocPointerDump(AllocPointer pointer){
  printf("\t%-10d@ %0#x\n", ((long*)pointer)[-1], pointer);
}

void
AllocSetDump(AllocSet set){
  int count;

  count = AllocSetIterate(set, AllocPointerDump);
  printf("\ttotal %d allocations\n", count);
}

int
AllocSetIterate(AllocSet set,
                void (*function)(AllocPointer pointer)){
  int          count = 0;
  AllocPointer pointer;

  AssertArg(AllocSetIsValid(set));

  for(pointer = AllocSetGetFirst(set);
      AllocPointerIsValid(pointer);
      pointer = AllocPointerGetNext(pointer)){
    if(PointerIsValid(function)){
      (*function)(pointer);
    }
    count += 1;
  }

  return (count);
}

static AllocPointer
AllocSetGetFirst(AllocSet set){
  AllocElem alloc;

  alloc = (AllocElem)OrderedSetGetHead(&set->setData);

  if(!AllocElemIsValid(alloc)){
    return (NULL);
  }

  return (AllocElemGetAllocPointer(alloc));
}

static AllocPointer
AllocPointerGetNext(AllocPointer pointer){
  AllocElem alloc;

  alloc = (AllocElem)OrderedElemGetSuccessor(&AllocPointerGetAllocElem(pointer)->elemData);

  if(!AllocElemIsValid(alloc)){
    return (NULL);
  }

  return (AllocElemAllocPointer(alloc));
}
