#ifndef BUFPAGE_H
#define BUFPAGE_H
#include "c.h"
#include "storage/itemid.h"
#include "storage/buf.h"
#include "storage/item.h"
#include "storage/off.h"

typedef uint16         LocationIndex;

typedef struct OpaqueData {
  uint16 od_pagesize;
} OpaqueData;

typedef OpaqueData *Paque;

typedef Pointer Page;

typedef struct PageHeaderData {
  LocationIndex    pd_lower;
  LocationIndex    pd_upper;
  LocationIndex    pd_special;
  OpaqueData       pd_opaque;
  ItemIdData       pd_linp[1];
} PageHeaderData;

typedef PageHeaderData *PageHeader;

#define PageGetItemId(page, offsetNumber)\
  ((ItemId) (&((PageHeader)(page))->pd_linp[(-1) + (offsetNumber)]))


extern Page         BufferGetPage(Buffer buffer);
extern Item         PageGetItem(Page page, ItemId itemId);
extern OffsetNumber PageGetMaxOffsetNumber(Page page);

#endif
