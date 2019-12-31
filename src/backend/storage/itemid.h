#ifndef ITEMID_H
#define ITEMID_H

#ifndef LP_USED
#define LP_USED 0x01
#endif

typedef struct ItemIdData {
  unsigned int lp_off:13,
    lp_flags:6,
    lp_len:13;
} ItemIdData;

typedef struct ItemIdData *ItemId;

#define ItemIdIsUsed(itemId) \
  (AssertMacro(ItemIdIsValid(itemId)) ?\
   (bool) (((itemId)->lp_flags & LP_USED) != 0):false)


#endif
