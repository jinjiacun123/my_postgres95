#ifndef NABSTIME_H
#define NABSTIME_H
#include<time.h>
#include "miscadmin.h"

typedef int32 AbsoluteTime;

#define EPOCH_ABSTIME    ((AbsoluteTime)0)
#define INVALID_ABSTIME  ((AbsoluteTime) 2147483647)
#define CURRENT_ABSTIME  ((AbsoluteTime) 2147483646)
#define NOEND_ABSTIME    ((AbsoluteTime) 2147483645)
#define NOSTART_ABSTIME  ((AbsoluteTime) -2147483647)

#define GetCurrentAbsoluteTime() \
  ((AbsoluteTime) getSystemTime())

#define getSystemTime() \
  ((time_t) (time(0l)))

#define AbsoluteTimeIsBackwardCompatiblyValid(time)\
  ((bool)(((AbsoluteTime)time) != INVALID_ABSTIME && \
          ((AbsoluteTime)time) > EPOCH_ABSTIME))

#define AbsoluteTimeIsBackwardCompatiblyReal(time)\
  ((bool)(((AbsoluteTime)time) < NOEND_ABSTIME &&                 \
          ((AbsoluteTime)time) > NOSTART_ABSTIME &&                               \
          ((AbsoluteTime)time) > EPOCH_ABSTIME))

#define HEAP_HASNULL          0x01

#define CURRENT_ABSTIME  ((AbsoluteTime)2147483646)


#endif
