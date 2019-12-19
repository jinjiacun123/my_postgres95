#ifndef PRS2LOCK_H
#define PRS2LOCK_H

#include "access/attnum.h"

typedef struct RewriteRule {
  Oid        ruleId;
  CmdType    event;
  AttrNumber attrno;
  Node       *qual;
  List       *actions;
  bool       isInstead;
} RewriteRule;

typedef struct RuleLock {
  int         numLocks;
  RewriteRule **rules;
} RuleLock;

#endif
