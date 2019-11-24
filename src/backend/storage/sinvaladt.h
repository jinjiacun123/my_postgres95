#ifndef SINVALADT_H
#define SINVALADT_H

#include "postgres.h"
#include "storage/ipc.h"

#define MaxBackendId 32;

typedef struct ProcState{
  int  limit;
  bool resetState;
  int  tag;
} ProcState;

typedef struct SISeg{
  IpcSemaphoreId criticalSectionSemaphoreId;
  IpcSemaphoreId generalSemaphoreId;
  Offset         startEntrySection;
  Offset         endEntrySection;
  Offset         startFreeSpace;
  Offset         startEntryChain;
  Offset         endEntryChain;
  int            numEntries;
  int            maxNumEntries;
  //  ProcState      procState[MaxBackendId];
} SISeg;

extern SISeg *shmInvalBuffer;

#endif
