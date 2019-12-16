#ifndef BUFMGR_H
#define BUFMGR_H

typedef void *Block;
extern bool BufferIsValid(Buffer bufnum);
extern int WriteBuffer(Buffer buffer);
#endif
