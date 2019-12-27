#include "nodes/nodes.h"
#include "nodes/parsenodes.h"
#include "nodes/relation.h"
#include "nodes/plannodes.h"
#include "nodes/execnodes.h"
#include "utils/elog.h"
#include "utils/fcache.h"

static Iter  *_readIter();
static Query *_readQuery();
static HInfo *_readHInfo();
static JInfo *_readJInfo();
static List  *toIntList(List *list);
static JInfo *_readJInfo();
static JoinMethod *_readJoinMethod();
static CInfo      *_readCInfo();
static MergeOrder *_readMergeOrder();
static JoinKey    *_readJoinKey();
static OrderKey   *_readOrderKey();
static HashPath   *_readhashPath();
static MergePath  *_readMergePath();
static JoinPath   *_readJoinPath();
static IndexPath  *_readIndexPath();
static Path       *_readPath();
static RangeTblEntry *_readRangeTblEntry();
static TargetEntry *_readTargetEntry();
static Rel         *_readRel();
static EState      *_readEState();
static Param       *_readParam();
static Oper        *_readOper();
static Func        *_readFunc();
static Const       *_readConst();
static Var         *_readVar();
static Array       *_readArray();
static ArrayRef    *_readArrayRef();
static Expr        *_readExpr();
static Resdom      *_readResdom();
static Hash        *_readHash();
static Unique      *_readUnique();
static Agg         *_readAgg();
static Sort        *_readSort();
static Temp        *_readTemp();
static IndexScan   *_readIndexScan();
static SeqScan     *_readSeqScan();
static Scan        *_readScan();
static HashJoin    *_readHashJoin();
static MergeJoin   *_readMergeJoin();
static NestLoop    *_readNestLoop();
static Join        *_readJoin();
static Append      *_readAppend();
static Existential *_readExistential();
static Result      *_readResult();
static Plan        *_readPlan();
static HashPath    *_readHashPath();

static void _getJoin(Join *node);
static void _getPlan(Plan *node);
static void _getScan(Scan *node);

static Datum readDatum(Oid type);

Node *
parsePlanString(){
  char *token;
  int  length;
  void *return_value;

  token = lsptok(NULL, &length);

  if(!strncmp(token, "PLAN", 4)){
    return_value = _readPlan();
  } else if(!strncmp(token, "RESULT", 6)){
    return_value = _readResult();
  } else if(!strncmp(token, "EXISTENTIAL", 11)){
    return_value = _readExistential();
  } else if(!strncmp(token, "APPEND", 6)){
    return_value = _readAppend();
  } else if(!strncmp(token, "JOIN", 4)){
    return_value = _readJoin();
  } else if(!strncmp(token, "NESTLOOP", 8)){
    return_value = _readNestLoop();
  } else if(!strncmp(token, "MERGEJOIN", 9)){
    return_value = _readMergeJoin();
  } else if(!strcmp(token, "HASHJOIN", 8)){
    return_value = _readHashJoin();
  } else if(!strncmp(token, "SCAN", 4)){
    return_value = _readScan();
  } else if(!strncmp(token, "SEQSCAN", 7)){
    return_value = _readSeqScan();
  } else if(!strncmp(token, "INDEXSCAN", 9)){
    return_value = _readIndexScan();
  } else if(!strncmp(token, "TEMP", 4)){
    return_value = _readTemp();
  } else if(!strncmp(token, "SORT", 4)){
    return_value = _readSort();
  } else if(!strncmp(token, "AGG", 3)){
    return_value = _readAgg();
  } else if(!strncmp(token, "UNIQUE", 4)){
    return_value = _readUnique();
  } else if(!strncmp(token, "hash", 4)){
    return_value = _readHash();
  } else if(!strncmp(token, "RESDOM", 6)){
    return_value = _readResdom();
  } else if(!strncmp(token, "EXPR", 4)){
    return_value = _readExpr();
  } else if(!strncmp(token, "ARRAYREF", 7)){
    return_value = _readArrayRef();
  } else if(!strncmp(token, "ARRAY", 5)){
    return_value = _readArray();
  } else if(!strncmp(token, "VAR", 3)){
    return_value = _readVar();
  } else if(!strncmp(token, "CONST", 5)){
    return_value = _readConst();
  } else if(!strncmp(token, "FUNC", 4)){
    return_value = _readFunc();
  } else if(!strncmp(token, "OPER", 4)){
    return_value = _readOper();
  } else if(!strncmp(token, "PARAM", 5)){
    return_value = _readParam();
  } else if(!strncmp(token, "ESTATE", 6)){
    return_value = _readEState();
  } else if(!strncmp(token, "REL", 3)){
    return_value = _readRel();
  } else if(!strncmp(token, "TLE", 3)){
    return_value = _readTargetEntry();
  } else if(!strncmp(token, "RTE", 3)){
    return_value = _readRangeTblEntry();
  } else if(!strncmp(token, "PATH", 4)){
    return_value = _readPath();
  } else if(!strncmp(token, "INDEXPATH", 9)){
    return_value = _readIndexPath();
  } else if(!strncmp(token, "JOINPATH", 8)){
    return_value = _readJoinPath();
  } else if(!strncmp(token, "MERGEPATH", 9)){
    return_value = _readMergePath();
  } else if(!strncmp(token, "HASHPATH", 8)){
    return_value = _readHashPath();
  } else if(!strncmp(token, "ORDERKEY", 8)){
    return_value = _readOrderKey();
  } else if(!strncmp(token, "JOINKEY", 7)){
    return_value = _readJoinKey();
  } else if(!strncmp(token, "MERGEORDER", 10)){
    return_value = _readMergeOrder();
  } else if(!strncmp(token, "CINFO", 5)){
    return_value = _readCInfo();
  } else if(!strncmp(token, "JOINMETHOD", 10)){
    return_value = _readJoinMethod();
  } else if(!strncmp(token, "JINFO", 5)){
    return_value = _readJInfo();
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
    NotifyStmt *n = makeNode(NotifyStmt);
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

static HInfo *
_readHInfo(){
  HInfo *local_node;
  char  *token;
  int   length;

  local_node = makeNode(HInfo);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->hashop = atoi(token);

  token = lsptok(NULL, &length);
  local_node->jmethod.jmkeys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->jmethod.clauses = nodeRead(true);

  return (local_node);
}

static JInfo *
_readJInfo(){
  JInfo *local_node;
  char  *token;
  int   length;

  local_node = makeNode(JInfo);

  token = lsptok(NULL, &length);
  local_node->otherrels = toIntList(nodeRead(true));

  token = lsptok(NULL, &length);
  local_node->jinfoclauseinfo = nodeRead(true);

  token = lsptok(NULL, &length);
  if(!strncmp(token, "true", 4)){
    local_node->mergesortable = true;
  } else {
    local_node->mergesortable = false;
  }

  token = lsptok(NULL, &length);

  if(!strncmp(token, "true", 4)){
    local_node->hashjoinable = true;
  } else {
    local_node->hashjoinable = false;
  }

  return(local_node);
}

static List *
toIntList(List *list){
  List *l;
  foreach(l, list){
    lfirst(l) = (void*)intVal(lfirst(l));
  }

  return list;
}

static JoinMethod *
_readJoinMethod(){
  JoinMethod *local_node;
  char       *token;
  int        length;

  local_node = makeNode(JoinMethod);

  token = lsptok(NULL, &length);
  local_node->jmkeys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->clauses = nodeRead(true);

  return(local_node);
}

static CInfo *
_readCInfo(){
  CInfo *local_node;
  char  *token;
  int   length;

  local_node = makeNode(CInfo);

  token = lsptok(NULL, &length);
  local_node->clause = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->selectivity = atof(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "true", 4)){
    local_node->notclause = true;
  } else {
    local_node->notclause = false;
  }

  token = lsptok(NULL, &length);
  local_node->indexids = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->mergesortorder = (MergeOrder*)nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->hashjoinoperator = atol(token);

  return (local_node);
}

static MergeOrder *
_readMergeOrder(){
  MergeOrder *local_node;
  char       *token;
  int        length;

  local_node = makeNode(MergeOrder);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->join_operator = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->left_operator = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->right_operator = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->left_type = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->right_type = atol(token);

  return (local_node);
}

static JoinKey *
_readJoinKey(){
  JoinKey *local_node;
  char    *token;
  int     length;

  local_node = makeNode(JoinKey);

  token = lsptok(NULL, &length);
  local_node->outer = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->inner = nodeRead(true);

  return(local_node);
}

static OrderKey *
_readOrderKey(){
  OrderKey *local_node;
  char     *token;
  int      length;

  local_node = makeNode(OrderKey);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->attribute_number = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->array_index = atoi(token);

  return(local_node);
}

static HashPath *
_readHashPath(){
  HashPath *local_node;
  char     *token;
  int      length;

  local_node = makeNode(HashPath);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.path.pathtype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.path.path_cost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->jpath.path.keys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->jpath.pathclauseinfo = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->jpath.outerjoinpath = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.innerjoinpath = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.path.outerjoincost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->jpath.path.joinid = toIntList(nodeRead(true));

  token = lsptok(NULL, &length);
  local_node->path_hashclauses = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->outerhashkeys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->innerhashkeys = nodeRead(true);

  return (local_node);
}

static MergePath *
_readMergePath(){
  MergePath *local_node;
  char      *token;
  int       length;

  local_node = makeNode(MergePath);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.path.pathtype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.path.path_cost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->jpath.path.keys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->jpath.pathclauseinfo = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.outerjoinpath = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.innerjoinpath = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->jpath.path.outerjoincost = (Cost) atof(token);

  token = lsptok(NULL, &length);
  local_node->jpath.path.joinid = toIntList(nodeRead(true));

  token = lsptok(NULL, &length);
  local_node->path_mergeclauses = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->outersortkeys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->innersortkeys = nodeRead(true);

  return(local_node);
}

static JoinPath *
_readJoinPath(){
  JoinPath *local_node;
  char     *token;
  int      length;

  local_node = makeNode(JoinPath);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->path.pathtype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->path.path_cost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->path.keys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->pathclauseinfo = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->outerjoinpath = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->innerjoinpath = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->path.outerjoincost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->path.joinid = toIntList(nodeRead(true));

  return(local_node);
}

static IndexPath *
_readIndexPath(){
  IndexPath *local_node;
  char      *token;
  int       length;

  local_node = makeNode(IndexPath);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->path.pathtype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->path.path_cost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->path.keys = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->indexid = toIntList(nodeRead(true));

  token = lsptok(NULL, &length);
  local_node->indexqual = nodeRead(true);

  return(local_node);
}

static Path *
_readPath(){
  Path *local_node;
  char *token;
  int  length;

  local_node = makeNode(Path);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->pathtype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->path_cost = (Cost)atof(token);

  token = lsptok(NULL, &length);
  local_node->keys = nodeRead(true);

  return(local_node);
}

static RangeTblEntry *
_readRangeTblEntry(){
  RangeTblEntry *local_node;
  char          *token;
  int           length;

  local_node = makeNode(RangeTblEntry);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  if(!strncmp(token, "\"null\"", 5)){
    local_node->relname = NULL;
  } else {
    token++;
    token[length -2 ] = '\0';

    local_node->relname = (char*)palloc(NAMEDATALEN);
    strcpy(local_node->relname, token);
    token[length -2 ] = '\"';
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->inh = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  if(!strncmp(token, "\"null\"", 5)){
    local_node->refname = NULL;
  } else {
    token++;
    token[length - 2] = '\0';

    local_node->refname = (char*)pstrdup(token);
    token[length -2 ] = '\"';
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->relid = atoi(token);

  return(local_node);
}

static TargetEntry *
_readTargetEntry(){
  TargetEntry *local_node;
  char        *token;
  int          length;

  local_node = makeNode(TargetEntry);

  token = lsptok(NULL, &length);
  local_node->resdom = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->expr = nodeRead(true);

  return(local_node);
}

static Rel *
_readRel(){
  Rel  *local_node;
  char *token;
  int  length;

  local_node = makeNode(Rel);

  token = lsptok(NULL, &length);
  local_node->relids = toIntList(nodeRead(true));

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "true", 4)){
    local_node->indexed = true;
  } else {
    local_node->indexed = false;
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->pages = (unsigned int)atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->tuples = (unsigned int)atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->size = (unsigned int)atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->width = (unsigned int)atoi(token);

  token = lsptok(NULL, &length);
  local_node->targetlist = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->pathlist = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  sscanf(token, "%x", &local_node->unorderedpath);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  sscanf(token, "%x", &local_node->cheapestpath);

  token = lsptok(NULL, &length);
  local_node->clauseinfo = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->joininfo = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->innerjoin = nodeRead(true);

  return(local_node);
}

static EState *
_readEState(){
  EState *local_node;
  char   *token;
  int    length;

  local_node = makeNode(EState);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->es_direction = atoi(token);

  token = lsptok(NULL, &length);

  local_node->es_range_table = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  sscanf(token, "%x", &local_node->es_result_relation_info);

  return(local_node);
}

static Param *
_readParam(){
  Param *local_node;
  char  *token;
  int   length;

  local_node = makeNode(Param);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->paramkind = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->paramid = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token++;
  token[length -2] = '\0';

  local_node->paramname = pstrdup(token);
  token[length -2] = '\"';

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->paramtype = atol(token);
  token = lsptok(NULL, &length);
  local_node->param_tlist = nodeRead(true);

  return(local_node);
}

static Oper *
_readOper(){
  Oper *local_node;
  char *token;
  int  length;

  local_node = makeNode(Oper);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->opno = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->opid = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->opresulttype = atol(token);

  local_node->op_fcache = (FunctionCache *)NULL;

  return(local_node);
}

static Func *
_readFunc(){
  Func *local_node;
  char *token;
  int  length;

  local_node = makeNode(Func);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->funcid = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->functype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "true", 4)){
    local_node->funcisindex = true;
  } else {
    local_node->funcisindex = false;
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->funcsize = stol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  local_node->func_fcache = (FunctionCache *)NULL;

  token = lsptok(NULL, &length);
  local_node->func_tlist = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->func_planlist = nodeRead(true);

  return(local_node);
}

static Const *
_readConst(){
  Const *local_node;
  char  *token;
  int   length;

  local_node = makeNode(Const);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->consttype  = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->constlen = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "true", 4)){
    local_node->constisnull = true;
  } else {
    local_node->constisnull = false;
  }

  token = lsptok(NULL, &length);

  if(local_node->constisnull){
    token = lsptok(NULL, &length);
  } else {
    local_node->constvalue = readDatum(local_node->consttype);
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "true", 4)){
    local_node->constbyval = true;
  } else {
    local_node->constbyval = false;
  }

  return(local_node);
}

static Var *
_readVar(){
  Var  *local_node;
  char *token;
  int  length;

  local_node = makeNode(Var);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->varno = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->varattno = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->vartype = (Oid)atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->varnoold = (Oid)atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->varoattno = (int) atol(token);

  return(local_node);
}

static Array *
_readArray(){
  Array *local_node;
  char  *token;
  int   length;

  local_node = makeNode(Array);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->arrayelemtype = (Oid) atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->arrayelemlength = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->arrayelembyval = (token[0] == 't') ? true: false;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->arraylow.indx[0] = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->arrayhigh.indx[0] = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->arraylen = atoi(token);

  return(local_node);
}

static ArrayRef *
_readArrayRef(){
  ArrayRef *local_node;
  char     *token;
  int      length;

  local_node = makeNode(ArrayRef);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->refelemtype = (Oid)atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->refattrlength = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->refelemlength = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->refelembyval = (token[0] == 't')? true:false;

  token = lsptok(NULL, &length);
  local_node->refupperindexpr = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->reflowerindexpr = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->refexpr = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->refassgnexpr = nodeRead(true);

  return (local_node);
}

static Expr *
_readExpr(){
  Expr *local_node;
  char *token;
  int  length;

  local_node = makeNode(Expr);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->typeOid = (Oid)atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  if(!strncmp(token, "op", 2)){
    local_node->opType = OP_EXPR;
  } else if(!strncmp(token, "func", 4)){
    local_node->opType = FUNC_EXPR;
  } else if(!strncmp(token, "or", 2)){
    local_node->opType = OR_EXPR;
  } else if(!strncmp(token, "and", 3)){
    local_node->opType = AND_EXPR;
  } else if(!strncmp(token, "not", 3)){
    local_node->opType = NOT_EXPR;
  }

  token = lsptok(NULL, &length);
  local_node->oper = nodeRead(true);

  token = lsptok(NULL, &length);
  local_node->args = nodeRead(true);

  return(local_node);
}

static Resdom *
_readResdom(){
  Resdom   *local_node;
  char     *token;
  int      length;

  local_node = makeNode(Resdom);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->resno = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->restype = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->reslen = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "\"null\"", 5)){
    local_node->resname = NULL;
  } else {
    token++;
    token[length -2] = '\0';

    local_node->resname = palloc(length);
    strcpy(local_node->resname, token);
    token[length -2] = '\"';
  }

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->reskey = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->reskeyop = (Oid)atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->resjunk = atoi(token);

  return(local_node);
}

static Hash *
_readHash(){
  Hash   *local_node;
  char   *token;
  int    length;

  local_node = makeNode(Hash);

  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  local_node->hashkey = (Var*)nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashtable = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashtablekey = 0;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashtablesize = 0;

  return(local_node);
}

static Unique *
_readUnique(){
  Unique       *local_node;
  char         *token;
  int          length;

  local_node = makeNode(Unique);

  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->tempid = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->keycount = atoi(token);

  return(local_node);
}

static Agg *
_readAgg(){
  Agg   *local_node;
  char  *token;
  int   length;

  local_node = makeNode(Agg);
  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->numAgg = atoi(token);

  return(local_node);
}

static Sort *
_readSort(){
  Sort  *local_node;
  char  *token;
  int   length;

  local_node = makeNode(Sort);

  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->tempid = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->keycount = atoi(token);

  return(local_node);
}

static Temp *
_readTemp(){
  Temp *local_node;
  char *token;
  int  length;

  local_node = makeNode(Temp);

  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->tempid = atol(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->keycount = atoi(token);

  return(local_node);
}

static IndexScan *
_readIndexScan(){
  IndexScan *local_node;
  char      *token;
  int       length;

  local_node = makeNode(IndexScan);

  _getScan((Scan*)local_node);

  token = lsptok(NULL, &length);
  local_node->indxid = toIntList(nodeRead(true));

  token = lsptok(NULL, &length);
  local_node->indxqual = nodeRead(true);

  return(local_node);
}

static SeqScan *
_readSeqScan(){
  SeqScan  *local_node;
  char     *token;
  int      length;

  local_node = makeNode(SeqScan);

  _getScan((Scan*)local_node);

  return(local_node);
}

static Scan *
_readScan(){
  Scan *local_node;
  char *token;
  int  length;

  local_node = makeNode(Scan);

  _getScan(local_node);

  return(local_node);
}

static HashJoin *
_readHashJoin(){
  HashJoin *local_node;
  char     *token;
  int      length;

  local_node = makeNode(HashJoin);

  _getJoin((Join*)local_node);

  token = lsptok(NULL, &length);
  local_node->hashclauses = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashjoinop = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashjointable = NULL;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashjointablekey = 0;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashjointablesize = 0;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->hashdone = false;

  return(local_node);
}

static MergeJoin *
_readMergeJoin(){
  MergeJoin *local_node;
  char      *token;
  int       length;

  local_node = makeNode(MergeJoin);

  _getJoin((Join*)local_node);

  token = lsptok(NULL, &length);
  local_node->mergeclauses = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->mergesortop = atol(token);

  return(local_node);
}

static NestLoop *
_readNestLoop(){
  NestLoop *local_node;

  local_node = makeNode(NestLoop);

  _getJoin((Join*)local_node);

  return(local_node);
}

static Join *
_readJoin(){
  Join *local_node;

  local_node = makeNode(Join);

  _getJoin(local_node);

  return(local_node);
}

static Append *
_readAppend(){
  Append *local_node;
  char   *token;
  int    length;

  local_node = makeNode(Append);

  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  local_node->unionplans = nodeRead(true);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  local_node->unionrelid = atoi(token);

  token = lsptok(NULL, &length);
  local_node->unionrtentries = nodeRead(true);

  return(local_node);
}

static Existential *
_readExistential(){
  Existential *local_node;
  local_node = makeNode(Existential);
  _getPlan((Plan*)local_node);
  return(local_node);
}

static Result *
_readResult(){
  Result *local_node;
  char   *token;
  int    length;

  local_node = makeNode(Result);

  _getPlan((Plan*)local_node);

  token = lsptok(NULL, &length);
  local_node->resconstantqual = nodeRead(true);

  return(local_node);
}

static Plan *
_readPlan(){
  Plan *local_node;
  local_node = makeNode(Plan);
  _getPlan(local_node);
  return(local_node);
}

static void
_getPlan(Plan *node){
  char *token;
  int  length;

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  node->cost = (Cost) atof(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  node->plan_size = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  node->plan_width = atoi(token);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);

  if(!strncmp(token, "nil", 3)){
    node->state = (EState*)NULL;
  } else {
    node->state = (EState*)!NULL;
  }

  token = lsptok(NULL, &length);
  node->targetlist = nodeRead(true);

  token = lsptok(NULL, &length);
  node->qual = nodeRead(true);

  token = lsptok(NULL, &length);
  node->lefttree = (Plan*)nodeRead(true);

  token = lsptok(NULL, &length);
  node->righttree = (Plan*)nodeRead(true);

  return;
}

static void
_getJoin(Join *node){
  _getPlan((Plan*)node);
}

static Datum
readDatum(Oid type){
  int         length;
  int         tokenLength;
  char        *token;
  bool        byValue;
  Datum       res;
  char        *s;
  int         i;

  byValue = get_typbyval(type);

  token  = lsptok(NULL, &tokenLength);
  length = atoi(token);
  token  = lsptok(NULL, &tokenLength);

  if(byValue){
    if(length > sizeof(Datum)){
      elog(WARN, "readValue: byval & length = %d", length);
    }
    s = (char *)(&res);
    for(i = 0; i < sizeof(Datum); i++){
      token = lsptok(NULL, &tokenLength);
      s[i] = (char) atoi(token);
    }
  } else if(length <= 0){
    s = NULL;
  } else if(length >= 1){
    s = (char *)palloc(length);
    Assert(s != NULL);
    for(i = 0; i < length; i++){
      token = lsptok(NULL, &tokenLength);
      s[i]  = (char) atoi(token);
    }
    res = PointerGetDatum(s);
  }

  token = lsptok(NULL, &tokenLength);
  if(token[0] != ']'){
    elog(WARN, "readValue: ']' expected, length =%d", length);
  }

  return(res);
}

static void
_getScan(Scan *node){
  char *token;
  int  length;

  _getPlan((Plan*)node);

  token = lsptok(NULL, &length);
  token = lsptok(NULL, &length);
  node->scanrelid = atoi(token);
}
