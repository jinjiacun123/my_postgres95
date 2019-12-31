#ifndef ISTRATE_H
#define ISTRATE_H
extern Size        AttributeNumberGetIndexStrategySize(AttrNumber maxAttributeNumber, StrategyNumber strategyNumber);
extern StrategyMap IndexStrategyGetStrategyMap(IndexStrategy  indexStrategy,
                                               StrategyNumber maxStrategyNum,
                                               AttrNumber     attrNum);
extern ScanKey     StrategyMapGetScanKeyEntry(StrategyMap    map,
                                              StrategyNumber strategyNumber);
extern ScanKey     StragegyMapGetScanKeyEntry(StrategyMap    map,
                                              StrategyNumber strategyNumber);

#endif
