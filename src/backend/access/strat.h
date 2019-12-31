#ifndef STRAT_H
#define STRAT_H
#include "postgres.h"
#include "access/skey.h"

#define AMStrategies(foo) 12

typedef struct StrategyMapData {
  ScanKeyData entry[1];
} StrategyMapData;

typedef StrategyMapData *StrategyMap;

typedef struct IndexStrategyData {
  StrategyMapData strategyMapData[1];
} IndexStrategyData;

typedef uint16            StrategyNumber;

typedef IndexStrategyData *IndexStrategy;

#endif
