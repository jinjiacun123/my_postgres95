#ifndef SHMEM_H
#define SHMEM_H
#include "storage/spin.h"

typedef unsigned long SHMEM_OFFSET;

extern SHMEM_OFFSET ShmemBase;
#define MAKE_PTR(xx_offs)\
  (ShmemBase+ ((unsigned long)(xx_offs)))

#endif
