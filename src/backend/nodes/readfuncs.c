#include "nodes/nodes.h"
#include "nodes/relation.h"
#include "utils/elog.h"

static Iter * _readIter();

Node *
parsePlanString(){
  char *token;
  int  length;
  void *return_value;

  token = lsptok(NULL, &length);

  if(!strncmp(token, "PLAN", 4)){
    return_value = readPlan();
  } else if(!strncmp(token, "RESULT", 6)){
    return_value = readResult();
  } else if(!strncmp(token, "EXISTENTIAL", 11)){
    return_value = readExistential();
  } else if(!strncmp(token, "APPEND", 6)){
    return_value = readAppend();
  } else if(!strncmp(token, "JOIN", 4)){
    return_value = readJoin();
  } else if(!strncmp(token, "NESTLOOP", 8)){
    return_value = readnestLoop();
  } else if(!strncmp(token, "MERGEJOIN", 9)){
    return_value = readMergeJoin();
  } else if(!strcmp(token, "HASHJOIN", 8)){
    return_value = readHashJoin();
  } else if(!strncmp(token, "SCAN", 4)){
    return_value = readScan();
  } else if(!strncmp(token, "SEQSCAN", 7)){
    return_value = readSeqScan();
  } else if(!strncmp(token, "INDEXSCAN", 9)){
    return_value = readIndexScan();
  } else if(!strncmp(token, "TEMP", 4)){
    return_value = readTemp();
  } else if(!strncmp(token, "SORT", 4)){
    return_value = readSort();
  } else if(!strncmp(token, "AGG", 3)){
    return_value = readAgg();
  } else if(!strncmp(token, "UNIQUE", 4)){
    return_value = readUnique();
  } else if(!strncmp(token, "hash", 4)){
    return_value = readHash();
  } else if(!strncmp(token, "RESDOM", 6)){
    return_value = readResdom();
  } else if(!strncmp(token, "EXPR", 4)){
    return_value = readExpr();
  } else if(!strncmp(token, "ARRAYREF", 7)){
    return_value = readArrayRef();
  } else if(!strncmp(token, "ARRAY", 5)){
    return_value = readArray();
  } else if(!strncmp(token, "VAR", 3)){
    return_value = readVar();
  } else if(!strncmp(token, "CONST", 5)){
    return_value = readConst();
  } else if(!strncmp(token, "FUNC", 4)){
    return_value = readFunc();
  } else if(!strncmp(token, "OPER", 4)){
    return_value = readOper();
  } else if(!strncmp(token, "PARAM", 5)){
    return_value = readParam();
  } else if(!strncmp(token, "ESTATE", 6)){
    return_value = readEState();
  } else if(!strncmp(token, "REL", 3)){
    return_value = readRel();
  } else if(!strncmp(token, "TLE", 3)){
    return_value = readTargetEntry();
  } else if(!strncmp(token, "RTE", 3)){
    return_value = readRangeTblEntry();
  } else if(!strncmp(token, "PATH", 4)){
    return_value = readPath();
  } else if(!strncmp(token, "INDEXPATH", 9)){
    return_value = readIndexPath();
  } else if(!strncmp(token, "JOINPATH", 8)){
    return_value = readJoinPath();
  } else if(!strncmp(token, "MERGEPATH", 9)){
    return_value = readMergePath();
  } else if(!strncmp(token, "HASHPATH", 8)){
    return_value = readHashPath();
  } else if(!strncmp(token, "ORDERKEY", 8)){
    return_value = readOrderKey();
  } else if(!strncmp(token, "JOINKEY", 7)){
    return_value = readJoinKey();
  } else if(!strncmp(token, "MERGEORDER", 10)){
    return_value = readMergeOrder();
  } else if(!strncmp(token, "CINFO", 5)){
    return_value = readCInfo();
  } else if(!strncmp(token, "JOINMETHOD", 10)){
    return_value = readJoinMethod();
  } else if(!strncmp(token, "JINFO", 5)){
    return_value = readJInfo();
  } else if(!strncmp(token, "HINFO", 5)){
    return_value = _readHInfo();
  } else if(!strncmp(token, "ITER", 4)){
    return_value = _readIter();
  } else if(!strncmp(token, "QUERY", 5)){
    return_value = _readQuery();
  } else {
    elog(WARN, "badly formatted planstring \"%.10s\"...\n", token);
  }

  return ((Node*)return_value);
}

static Query *
_readQuery(){
  Query *local_node;
  char  *token;
  int   length;

  local_node = makeNode(Query);

  token                   = lsptok(NULL, &length);
  token                   = lsptok(NULL, &length);
  local_node->commandType = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  if(token[0] == '"' && token[1] == '"')
    local_node->utilityStmt = NULL;
  else {
    NotifyStmt *n = makeNode(NofifyStmt);
    n->relname    = palloc(length +1);
    strncpy(n->relname, token, length);
    n->relname[length] = '\0';
    local_node->utilityStmt = (Node*)n;
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->resultRelation = atoi(token);

  token = lsptok(NULL, &length);
  local_node->rtable = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  if(token[0] == '"' && token[1] == '"')
    local_node->uniqueFlag = NULL;
  else {
    local_node->uniqueFlag = palloc(length + 1);
    strncpy(local_node->uniqueFlag, token, length);
    local_node->uniqueFlag[length] = '\0';
  }

  token = lsptok(NULL, &length);
  local_node->targetList = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->qual = nodeRead(true);

  return (local_node);
}

static Iter *
_readIter(){
  Iter *local_node;
  char *token;
  int  length;

  local_node = makeNode(Iter);

  token = lsptok(NULL, &length);
  local_node->iterexpr = nodeRead(true);

  return(local_node);
}
