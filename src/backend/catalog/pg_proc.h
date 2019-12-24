#ifndef PG_PROC_H
#define PG_PROC_H
#include "postgres.h"
#define ObjectIdEqualRegProcedure    184
#define Character16EqualRegProcedure 490
DATA(insert OID = 28 ( boolin  PGUID 11 f t f 1 f 16 "0" 100 0 0 100 foo bar));
DATA(insert OID = 29 ( boolout PGUID 11 f t f 1 f 23 "0" 100 0 0 100 foo bar));
DATA(insert OID = 47 ( textout PGUID 11 f t f 1 f 23 "0" 100 0 0 100 foo bar));
#endif
