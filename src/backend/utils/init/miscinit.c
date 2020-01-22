#include "postgres.h"
#include "miscadmin.h"

static ProcessingMode Mode = NoProcessing;
extern char *DatabaseName;

bool
IsBootstrapProcessingMode(){
  return ((bool)(Mode == BootstrapProcessing));
}

bool
IsInitProcessingMode(){
  return ((bool)(Mode == InitProcessing));
}

char *
GetDatabaseName(){
  return DatabaseName;
}
