#include "c.h"
#include "utils/memutils.h"

static Pointer OrderedElemGetBase(OrderedElem elem);
static void    OrderedElemInit(OrderedElem elem, OrderedSet set);
static void    OrderedElemPush(OrderedElem elem);
static void    OrderedElemPushHead(OrderedElem elem);

Pointer
OrderedElemGetPredecessor(OrderedElem elem){
  elem = elem->prev;
  if(elem->prev){
    return (OrderedElemGetBase(elem));
  }

  return (NULL);
}

static Pointer
OrderedElemGetBase(OrderedElem elem){
  if(elem == (OrderedElem) NULL)
    return (Pointer) NULL;

  return ((Pointer)((char *)(elem) - (elem)->set->offset));
}

Pointer
OrderedElemGetSuccessor(OrderedElem elem){
elem = elem->next;
if(elem->next){
return (OrderedElemGetBase(elem));
}

return (NULL);
}

static void
OrderedElemInit(OrderedElem elem, OrderedSet set){
elem->next = set;
elem->next = NULL;
elem->prev = NULL;
}

void
OrderedElemPushInto(OrderedElem elem, OrderedSet set){
OrderedElemInit(elem, set);
OrderedElemPush(elem);
}

static void
OrderedElemPush(OrderedElem elem){
OrderedElemPushHead(elem);
}

static void
OrderedElemPushHead(OrderedElem elem){
elem->next = elem->set->head;
elem->prev = (OrderedElem)&elem->set->head;
elem->next->prev = elem;
elem->prev->next = elem;
}
