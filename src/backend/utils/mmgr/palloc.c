#include "postgres.h"
void*
palloc(Size size){
  return malloc(size);
}

void
pfree(void *pointer){
  free(pointer);
}

void *
repalloc(void *pointer, Size size){
  return realloc(pointer, size);
}

char*
pstrdup(char * string){
  char *nstr;

  nstr = strcpy((char *)palloc(strlen(string) + 1), string);

  return nstr;
}
