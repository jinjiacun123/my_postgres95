#include "postgres.h"
int
namestrcpy(Name name, char *str){
  if(!name || !str)
    return(-2);
  memset(name->data, 0, sizeof(NameData));
  (void)strncpy(name->data, str, NAMEDATALEN);
  return(0);
}
