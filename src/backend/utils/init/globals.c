#include "storage/sinval.h"
#include "storage/sinvaladt.h"
#include "catalog/catname.h"

BackendId MyBackendId;

int       Quiet = 1;
char *    DataDir;
Oid       MyDatabaseId = InvalidOid;

char *SharedSystemRelationNames[] = {
  DatabaseRelationName,
  DefaultsRelationName,
  DemonRelationName,
  GroupRelationName,
  HostsRelationName,
  LogRelationName,
  MagicRelationName,
  ServerRelationName,
  TimeRelationName,
  UserRelationName,
  VariableRelationName,
  0
};
