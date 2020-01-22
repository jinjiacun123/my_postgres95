
#ifndef POSTGRES_H
#define POSTGRES_H
#include "c.h"

#define FirstCommandId 0

typedef uint32 TransactionId;
typedef uint16 CommandId;
typedef uint32 Oid;
typedef int32  int4;
typedef int16  int2;

typedef int2 int28[8];
typedef Oid  oid8[8];

#ifndef NAMEDATALEN
#define NAMEDATALEN 16
#endif

#define BOOTSTRAP
#define CATALOG(x)  typedef struct CppConcat(FormData_,x)

#define DATA(x) extern int errno

#define InvalidOid           0
#define OidIsValid(objectId) ((bool) (objectId != InvalidOid))

typedef struct nameData {
  char data[NAMEDATALEN];
} NameData;
typedef NameData *Name;

struct varlena {
  int32 vl_len;
  char  vl_dat[1];
};

#define VARSIZE(PTR) (((struct varlena *)(PTR))->vl_len)
#define VARDATA(PTR) (((struct varlena *)(PTR))->vl_dat)
#define VARHDRSZ     sizeof(int32)

#define RegProcedureIsValid(p) OidIsValid(p)

typedef struct varlena bytea;
typedef struct varlena text;

typedef Oid regproc;
typedef Oid RegProcedure;
typedef char * ((*func_ptr)());

#define STATUS_OK    (0)
#define STATUS_ERROR (-1)


#endif
