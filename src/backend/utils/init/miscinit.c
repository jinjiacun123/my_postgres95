#include "postgres.h"
#include "miscadmin.h"

static ProcessingMode Mode = NoProcessing;

bool
IsBootstrapProcessingMode(){
  return ((bool)(Mode == BootstrapProcessing));
}
