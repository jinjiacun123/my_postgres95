#include "postgres.h"

static bool LockingIsDisabled;

bool
LockingDisabled(){
  return LockingIsDisabled;
}
