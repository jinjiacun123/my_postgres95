#ifndef HASHJOIN_H
#define HASHJOIN_H
#include "storage/ipc.h"

typedef int    RelativeAddr;

typedef struct HashTableData {
  int                 nbuckets;
  int                 totalbuckets;
  int                 bucketsize;
  IpcMemoryId         shmid;
  RelativeAddr        top;
  RelativeAddr        bottom;
  RelativeAddr        overflownext;
  RelativeAddr        batch;
  RelativeAddr        readbuf;
  int                 nbatch;
  RelativeAddr        outerbatchNames;
  RelativeAddr        outerbatchPos;
  RelativeAddr        innerbatchNames;
  RelativeAddr        innerbatchPos;
  int                 curbatch;
  int                 mprocess;
  int                 pcount;
} HashTableData;

typedef HashTableData  *HashJoinTable;

typedef struct OverflowTupleData {
  RelativeAddr tuple;
  RelativeAddr next;
} OverflowTupleData;

typedef OverflowTupleData *OverflowTuple;

typedef struct HashBucketData{
  RelativeAddr top;
  RelativeAddr bottom;
  RelativeAddr firstotuple;
  RelativeAddr lastotuple;
} HashBucketData;

typedef HashBucketData *HashBucket;





#endif
