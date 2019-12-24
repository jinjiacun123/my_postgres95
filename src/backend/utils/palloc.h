#ifndef PALLOC_H
#define PALLOC_H
#include "c.h"

extern void  pfree(void *pointer);
extern void* palloc(Size size);
extern void* repalloc(void *pointer, Size size);

#endif
