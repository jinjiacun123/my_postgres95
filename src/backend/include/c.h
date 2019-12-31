#ifndef C_H
#define C_H

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int Index;

#define false ((char) 0)
#define true ((char) 1)

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef char bool;
typedef bool *BoolPtr;

typedef signed   short int16;
typedef signed   int   int32;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef signed   int Offset;
typedef char *Pointer;

typedef uint8   bits8;
typedef uint16  bits16;

typedef unsigned long Datum;

#define CppConcat(x,y) x##y

#define Assert(condition)
#define AssertMacro(condition) true
#define AssertArg(condition)
#define AssertState(condition)

typedef unsigned int Size;

#define PointerIsValid(pointer) (bool)((void*)(pointer) != NULL)

#ifndef offsetof
#define offsetof(type, field) ((long) ((type *)0)->field)
#endif

#define SET_4_BYTES(value) (((Datum) (value)) & 0xffffffff)

#define NameGetDatum(X) PointerGetDatum((Pointer) X)
#define PointerGetDatum(X) ((Datum)X)
#define ObjectIdGetDatum(X) ((Datum) SET_4_BYTES(X))

#define MAXDIM 6
typedef struct {
  int indx[MAXDIM];
} IntArray;

typedef unsigned long Datum;
typedef Datum         *DatumPtr;





#endif
