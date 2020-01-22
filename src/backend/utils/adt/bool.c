#include "postgres.h"
#include "utils/rel.h"
#include "utils/elog.h"

int32
boolin(char *b){
  if(b == NULL)
    elog(WARN, "Bad input string for type bool");
  return((int32) (*b == 't') || (*b == 'T'));
}

char *
boolout(long b){
  char *result = (char *)palloc(2);
  *result = (b) ? 't':'f';
  result[1] = '\0';
  return(result);
}
