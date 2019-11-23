#ifndef NABSTIME_H
#define NABSTIME_H
#include<time.h>
#include "miscadmin.h"

typedef int32 AbsoluteTime;

#define GetCurrentAbsoluteTime() \
  ((AbsoluteTime) getSystemTime())

#define getSystemTime() \
  ((time_t) (time(0l)))

#endif
