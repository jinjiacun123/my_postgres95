#include "storage/buf_internals.h"

long       *PrivateRefCount;
BufferDesc *BufferDescriptors;
long       *LastRefCount;
SPINLOCK   BufMgrLock;
int        lateWrite = TRUE;
