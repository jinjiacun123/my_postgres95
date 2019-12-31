#ifndef TUPMACS_H
#define TUPMACS_H
#define fetchatt(A, T)\
  ((*(A))->attbyval && (*(A))->attlen != -1\
   ? ((*(A))->attlen > sizeof(int16) \
      ? (char *)(long) *((int32 *)(T)) \
      :((*(A))->attlen < sizeof(int16) \
        ? (char *)(long) *((char *)(T))\
        :(char *)(long) *((int16 *)(T))))\
   : (char *)(T))



#define att_isnull(ATT, BITS) (!((BITS)[(ATT) >> 3] & (1 << ((ATT) & 0x07))))

#endif
