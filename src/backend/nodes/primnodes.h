#ifndef PRIMNODES_H
#define PRIMNODES_H
#include "postgres.h"
#include "access/attnum.h"
#include "utils/fcache.h"

typedef enum OpType {
  OP_EXPR, FUNC_EXPR, OR_EXPR, AND_EXPR, NOT_EXPR
} OpType;

typedef struct Aggreg {
  NodeTag type;
  char    *aggname;
  Oid     basetype;
  Oid     aggtype;
  Node    *target;
  int     aggno;
} Aggreg;

typedef struct Resdom {
  NodeTag      type;
  AttrNumber   resno;
  Oid          restype;
  int          reslen;
  char         *resname;
  Index        reskey;
  Oid          reskeyop;
  int          resjunk;
} Resdom;

typedef struct Expr {
  NodeTag        type;
  Oid            typeOid;
  OpType         opType;
  Node           *oper;
  List           *args;
} Expr;

typedef struct ArrayRef {
  NodeTag      type;
  int          refattrlength;
  int          refelemlength;
  Oid          refelemtype;
  bool         refelembyval;
  List         *refupperindexpr;
  List         *reflowerindexpr;
  Node         *refexpr;
  Node         *refassgnexpr;
} ArrayRef;

typedef struct Array {
  NodeTag     type;
  Oid         arrayelemtype;
  int         arrayelemlength;
  bool        arrayelembyval;
  int         arrayndim;
  IntArray    arraylow;
  IntArray    arrayhigh;
  int         arraylen;
} Array;

typedef struct Const {
  NodeTag   type;
  Oid       consttype;
  Size      constlen;
  Datum     constvalue;
  bool      constisnull;
  bool      constbyval;
  bool      constisset;
} Const;

typedef struct Func {
  NodeTag          type;
  Oid              funcid;
  Oid              functype;
  bool             funcisindex;
  int              funcsize;
  FunctionCachePtr func_fcache;
  List             *func_tlist;
  List             *func_planlist;
} Func;

typedef struct Oper {
  NodeTag          type;
  Oid              opno;
  Oid              opid;
  Oid              opresulttype;
  int              opsize;
  FunctionCachePtr op_fcache;
} Oper;

typedef struct Param {
  NodeTag         type;
  int             paramkind;
  AttrNumber      paramid;
  char            *paramname;
  Oid             paramtype;
  List            *param_tlist;
} Param;

typedef struct Fjoin {
  NodeTag     type;
  bool        fj_initialized;
  int         fj_nNodes;
  List        *fj_innerNode;
  DatumPtr    fj_results;
  BoolPtr     fj_alwaysDone;
} Fjoin;

#endif
