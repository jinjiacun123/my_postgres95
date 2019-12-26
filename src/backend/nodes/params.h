#ifndef PARAMS_H
#define PARAMS_H
#include "c.h"
#include "access/attnum.h"

typedef struct ParamListInfoData {
  int        kind;
  char       *name;
  AttrNumber id;
  Oid        type;
  Size       length;
  bool       isnull;
  bool       byval;
  Datum      value;
} ParamListInfoData;


typedef ParamListInfoData *ParamListInfo;









#endif
