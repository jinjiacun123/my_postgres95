#ifndef HASHJOIN_H
#define HASHJOIN_H


typedef struct HashTableData {
  int                 nbuckets;
  int                 totalbuckets;
  int                 bucketsize;
  IpcMemoryId         shmid;
  RelationAddr        top;
  RelationAddr        bottom;
  RelationAddr        overflownext;
  RelationAddr        batch;
  RelationAddr        readbuf;
  int                 nbatch;
  RelationAddr        outerbatchNames;
  RelationAddr        outerbatchPos;
  RelationAddr        innerbatchNames;
  RelationAddr        innerbatchPos;
  int                 curbatch;
  int                 mprocess;
  int                 pcount;
} HashTableData;

typedef HashTableData  *HashJoinTable;

#endif
