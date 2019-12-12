#ifndef C_H
#define C_H

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int Index;

#define false ((char) 0)
#define true ((char) 1)

typedef char bool;

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

#define AssertArg(condition);
#define AssertState(condition);

typedef unsigned int Size;

#define PointerIsValid(pointer) (bool)((void*)(pointer) != NULL)

#endif
