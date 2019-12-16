#include "postgres.h"
#include "utils/catcache.h"
#include "utils/mcxt.h"

static Pointer GlobalMemoryAlloc(GlobalMemory this, Size size);
static void    GlobalMemoryFree(GlobalMemory this, Pointer pointer);
static Pointer GlobalMemoryRealloc(GlobalMemory this, Pointer pointer, Size size);
static char    *GlobalMemoryGetName(GlobalMemory this);
static void    GlobalMemoryDump(GlobalMemory this);
static void    DumpGlobalMemories(void);

static struct MemoryContextMethodsData GlobalContextMethodsData = {
  GlobalMemoryAlloc,
  GlobalMemoryFree,
  GlobalMemoryRealloc,
  GlobalMemoryGetName,
  GlobalMemoryDump
};
static struct GlobalMemory TopGlobalMemoryData = {
  T_GlobalMemory,
  &GlobalContextMethodsData,
  {{0}},
  "TopGlobal",
  {0}
};

MemoryContext TopMemoryContext = (MemoryContext)&TopGlobalMemoryData;

GlobalMemory
CreateGlobalMemory(char *name){
  GlobalMemory  context;
  MemoryContext savecxt;

  AssertState(MemoryContextEnabled);

  savecxt = MemoryContextSwitchTo(TopMemoryContext);

  return (context);
}

MemoryContext
MemoryContextSwitchTo(MemoryContext context){
  MemoryContext old;

  AssertState(MemoryContextEnabled);
  AssertArg(MemoryContextIsValid(context));

  //old                  = CurrentMemoryContext;
  //CurrentMemoryContext = context;

  return (old);
}

static Pointer
GlobalMemoryAlloc(GlobalMemory this, Size size){
  return (AllocSetAlloc(&this->setData, size));
}

static void
GlobalMemoryFree(GlobalMemory this,
                 Pointer      pointer){
  AllocSetFree(&this->setData, pointer);
}

static char *
GlobalMemoryGetName(GlobalMemory this)
{
  return (this->name);
}

static void
GlobalMemoryDump(GlobalMemory this){
  GlobalMemory context;

  printf("--n%s:\n", GlobalMemoryGetName(this));

  context = (GlobalMemory)OrderedElemGetPredecessor(&this->elemData);
  if(PointerIsValid(context)){
    printf("\tpredecessor=%s", GlobalMemoryGetName(context));
  }

  context = (GlobalMemory)OrderedElemGetSuccessor(&this->elemData);
  if(PointerIsValid(context)){
    printf("\tsuccessor=%s\n", GlobalMemoryGetName(context));
  }

  AllocSetDump(&this->setData);
}

bool
OrderedSetContains(OrderedSet set, OrderedElem elem){
  return ((bool)(elem->set == set && (elem->next || elem->prev)));
}

static Pointer
GlobalMemoryRealloc(GlobalMemory this,
                    Pointer      pointer,
                    Size         size){
  return (AllocSetRealloc(&this->setData, pointer, size));
}
