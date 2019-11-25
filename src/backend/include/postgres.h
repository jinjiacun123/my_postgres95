
#ifndef POSTGRES_H
#define POSTGRES_H
#include "c.h"

#define FirstCommandId 0

typedef uint32 TransactionId;
typedef uint16 CommandId;
typedef uint32 Oid;
typedef int32  int4;
typedef int16  int2;

#define BOOTSTRAP
#define CATALOG(x)  typedef struct CppConcat(FormData_,x)

typedef struct nameData {
  char data[NAMEDATALEN];
} NameData;

typedef Oid RegProcedure;
typedef char * ((*func_ptr)());

#endif
