#include "postgres.h"
#include "utils/hsearch.h"

static uint32 call_hash(HTAB *hashp, char *k, int len);
static int bucket_alloc(HTAB *hashp);
#define GET_SEG(hp, seg_num)\
  (SEGMENT) (((unsigned long) (hp)->segbase) + (hp)->dir[seg_num])
#define GET_BUCKET(hp, bucket_offs)\
  (ELEMENT *) (((unsigned long)(hp)->segbase) + bucket_offs)
#define MAKE_HASHOFFSET(hp, ptr)\
  (((unsigned long)ptr) - ((unsigned long) (hp)->segbase))

long *
hash_search(HTAB       *hashp,
            char       *keyPtr,
            HASHACTION action,
            bool       *foundPtr){
  uint32           bucket;
  long             segment_num;
  long             segment_ndx;
  SEGMENT          segp;
  register ELEMENT *curr;
  HHDR             *hctl;
  BUCKET_INDEX     currIndex;
  BUCKET_INDEX     *prevIndexPtr;
  char *           destAddr;
  static struct State {
    ELEMENT       *currElem;
    BUCKET_INDEX  currIndex;
    BUCKET_INDEX  *prevIndex;
  } saveState;

  Assert((hashp && keyPtr));
  Assert((action == HASH_FIND)
         ||(action == HASH_REMOVE)
         ||(action == HASH_ENTER)
         ||(action == HASH_FIND_SAVE)
         ||(action == HASH_REMOVE_SAVED));

  hctl = hashp->hctl;

  if(action == HASH_REMOVE_SAVED){
    curr         = saveState.currElem;
    currIndex    = saveState.currIndex;
    prevIndexPtr = saveState.prevIndex;
    Assert(saveState.currElem && !(saveState.currElem = 0));
  } else {
    bucket      = call_hash(hashp, keyPtr, hctl->keysize);
    segment_num = bucket >> hctl->sshift;
    segment_ndx = bucket & (hctl->ssize -1);
    segp        = GET_SEG(hashp, segment_num);
    Assert(segp);
    prevIndexPtr = &segp[segment_ndx];
    currIndex    = *prevIndexPtr;
    for(curr = NULL; currIndex != INVALID_INDEX;){
      curr = GET_BUCKET(hashp, currIndex);
      if(! memcmp((char *)&(curr->key), keyPtr, hctl->keysize)){
        break;
      }
      prevIndexPtr = &(curr->next);
      currIndex    = *prevIndexPtr;
    }
  }

  *foundPtr = (bool)(currIndex != INVALID_INDEX);
  switch(action){
  case HASH_ENTER:
  if(currIndex != INVALID_INDEX)
    return(&(curr->key));
  break;
  case HASH_REMOVE:
  case HASH_REMOVE_SAVED:
    if(currIndex != INVALID_INDEX) {
      Assert(hctl->nkeys > 0);
      hctl->nkeys--;
      *prevIndexPtr         = curr->next;
      curr->next            = hctl->freeBucketIndex;
      hctl->freeBucketIndex = currIndex;
      return (&(curr->key));
    }
    return ((long *)TRUE);
  case HASH_FIND:
    if(currIndex != INVALID_INDEX)
      return (&(curr->key));
    return ((long *)TRUE);
  case HASH_FIND_SAVE:
    if(currIndex != INVALID_INDEX){
      saveState.currElem  = curr;
      saveState.prevIndex = prevIndexPtr;
      saveState.currIndex = currIndex;
      return (&(curr->key));

    }
    return ((long *)TRUE);
  default:
    return (NULL);
  }
  Assert(currIndex == INVALID_INDEX);
  currIndex = hctl->freeBucketIndex;
  if(currIndex == INVALID_INDEX){
    if(! bucket_alloc(hashp)){
      return (NULL);
    }
    currIndex = hctl->freeBucketIndex;
  }
  Assert(currIndex != INVALID_INDEX);

}

static int
bucket_alloc(HTAB *hashp){
  int          i;
  ELEMENT      *tmpBucket;
  long         bucketSize;
  BUCKET_INDEX tmpIndex,lastIndex;

  bucketSize = sizeof(BUCKET_INDEX) + hashp->hctl->keysize + hashp->hctl->datasize;
  bucketSize += sizeof(long *) - (bucketSize % sizeof(long *));
  tmpBucket = (ELEMENT *)hashp->alloc((unsigned long) BUCKET_ALLOC_INCR * bucketSize);
  if(! tmpBucket){
    return (0);
  }
  tmpIndex = MAKE_HASHOFFSET(hashp, tmpBucket);
  lastIndex = hashp->hctl->freeBucketIndex;
  hashp->hctl->freeBucketIndex = tmpIndex;

  for(i = 0; i < (BUCKET_ALLOC_INCR-1); i++){
    tmpBucket = GET_BUCKET(hashp, tmpIndex);
    tmpIndex  += bucketSize;
    tmpBucket->next = tmpIndex;
  }

  tmpBucket->next = lastIndex;
  return (1);
}

static uint32
call_hash(HTAB *hashp, char *k , int len){
  long hash_val, bucket;
  HHDR *hctl;

  hctl = hashp->hctl;
  hash_val = hashp->hash(k, len);

  bucket = hash_val & hctl->high_mask;
  if( bucket > hctl->max_bucket ){
    bucket = bucket & hctl->low_mask;
  }

  return (bucket);
}
