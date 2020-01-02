#ifndef BIT_H
#define BIT_H

typedef bits8    *BitArray;
typedef uint32   BitIndex;

#define BitsPerByte 8

extern bool BitArrayBitIsSet(BitArray  bitArray,
                             BitIndex  bitIndex);

#endif
