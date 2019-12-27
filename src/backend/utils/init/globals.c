#include "storage/sinval.h"
#include "storage/sinvaladt.h"

BackendId MyBackendId;

int       Quiet = 1;
char *    DataDir;
Oid       MyDatabaseId = InvalidOid;

char *SharedSystemRelationNames[] = {
  DatabaseRelationName,
  DefaultsRelationname,
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
