#ifndef BUFMGR_H
#define BUFMGR_H
#include "c.h"
#include "machine.h"
#include "storage/buf_internals.h"

#define P_NEW InvalidBlockNumber

typedef void *Block;
extern bool BufferIsValid(Buffer bufnum);
extern int WriteBuffer(Buffer buffer);
#endif
