#include "postgres.h"
void*
palloc(Size size){
  return malloc(size);
}

void
pfree(void *pointer){
  free(pointer);
}
