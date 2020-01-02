#include "postgres.h"
#include "utils/bit.h"

bool
BitArrayBitIsSet(BitArray  bitArray,
                 BitIndex  bitIndex){
  return ((bool)(((bitArray[bitIndex/BitsPerByte] & (1 <<(BitsPerByte -(bitIndex % BitsPerByte) -1))) != 0)?1:0));
}
