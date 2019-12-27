#include "miscadmin.h"
#include "storage/buf_internals.h"

long       *PrivateRefCount;
BufferDesc *BufferDescriptors;
long       *LastRefCount;
SPINLOCK   BufMgrLock;
int        LateWrite = TRUE;
int        NBuffers  = NDBUFS;

int        ReadBufferCount;
int        BufferHitCount;
int        Free_List_Descriptor;
