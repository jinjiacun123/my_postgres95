#ifndef CATALOG_H
#define CATALOG_H
#include "access/tupdesc.h"

extern Oid  newoid(void);
extern bool IsSystemRelationName(char *relname);
extern bool IsSharedSystemRelationName(char *relname);

#endif
