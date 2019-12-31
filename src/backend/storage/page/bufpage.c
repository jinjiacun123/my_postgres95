#include "postgres.h"
#include "storage/bufpage.h"
#include "storage/itemid.h"
#include "storage/item.h"

Page
BufferGetPage(Buffer buffer){
  return (Page) BufferGetBlock(buffer);
}

Item
PageGetItem(Page page, ItemId itemId){
  Item   item;

  Assert(PageIsValid(page));
  Assert((*itemId).lp_flags & LP_USED);

  item = (Item) (((char *)page) + (*itemId).lp_off);

  return (item);
}

OffsetNumber
PageGetMaxOffsetNumber(Page page){
  LocationIndex low;
  OffsetNumber  i;

  low = ((PageHeader)page)->pd_lower;
  i = (low - (sizeof(PageHeaderData) - sizeof(ItemIdData)))/ sizeof(ItemIdData);

  return(i);
}
