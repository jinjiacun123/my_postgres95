#include "postgres.h"
void*
palloc(Size size){
  return malloc(size);
}
