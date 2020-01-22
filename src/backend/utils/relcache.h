#ifndef RELCACHE_H
#define RELCACHE_H
#include<sys/types.h>

extern void      RelationRegisterRelation(Relation relation);
extern Relation  RelationNameCacheGetRelation(char *relationName);
extern void      RelationClose(Relation relation);
extern Relation  RelationIdCacheGetRelatin(Oid relationId);
#endif
