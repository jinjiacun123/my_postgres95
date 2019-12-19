#ifndef HSEARCH_H
#define HSEARCH_H

#define INVALID_INDEX     (0)
#define BUCKET_ALLOC_INCR (30)

typedef enum {
  HASH_FIND,
  HASH_ENTER,
  HASH_REMOVE,
  HASH_FIND_SAVE,
  HASH_REMOVE_SAVED
} HASHACTION;

typedef struct element {
  unsigned long next;
  long           key;
} ELEMENT;

typedef unsigned long BUCKET_INDEX;
typedef BUCKET_INDEX *SEGMENT;
typedef unsigned long SEG_OFFSET;
typedef struct hashhdr {
  long bsize;
  long bshift;
  long dsize;
  long ssize;
  long sshift;
  long max_bucket;
  long high_mask;
  long low_mask;
  long ffactor;
  long nkeys;
  long nsegs;
  long keysize;
  long datasize;
  long max_dsize;
  BUCKET_INDEX freeBucketIndex;
} HHDR;

typedef struct htab {
  HHDR       *hctl;
  long       (*hash)();
  char       *segbase;
  SEG_OFFSET *dir;
  long       *(*alloc)();
} HTAB;


#endif
