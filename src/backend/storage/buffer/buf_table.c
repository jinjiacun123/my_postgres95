#include "postgres.h"
#include "storage/buf_internals.h"
#include "utils/hsearch.h"
#include "utils/elog.h"

static HTAB *SharedBufHash;

typedef struct lookup {
  BufferTag  key;
  Buffer     id;
} LookupEnt;


bool
BufTableDelete(BufferDesc *buf){
  LookupEnt *result;
  bool      found;

  if(buf->flags & BM_DELETED){
    return(TRUE);
  }

  buf->flags |= BM_DELETED;

  result = (LookupEnt *)hash_search(SharedBufHash, (char *)&(buf->tag), HASH_REMOVE, &found);

  if(!(result && found)){
    elog(WARN, "BufTableDelete: BufferLookup table corrupted");
    return(FALSE);
  }

  return(TRUE);
}

BufferDesc *
BufTableLookup(BufferTag *tagPtr){
  LookupEnt  *result;

  return (&(BufferDescriptors[result->id]));
}

bool
BufTableInsert(BufferDesc *buf){

  return(TRUE);
}
