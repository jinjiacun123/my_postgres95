#ifndef RELSCAN_H
#define RELSCAN_H

#include "storage/buf.h"
#include "storage/itemptr.h"
#include "access/htup.h"
#include "utils/rel.h"
#include "utils/tqual.h"

typedef ItemPointerData MarkData;

typedef struct HeapScanDescData {
  Relation        rs_rd;
  HeapTuple       rs_ptup;
  HeapTuple       rs_ctup;
  HeapTuple       rs_ntup;
  Buffer          rs_pbuf;
  Buffer          rs_cbuf;
  Buffer          rs_nbuf;
  ItemPointerData rs_mctid;
  ItemPointerData rs_mntid;
  ItemPointerData rs_mcd;
  bool            rs_atend;
  TimeQual        rs_tr;
  uint16          rs_cdelta;
  uint16          rs_nkeys;
  ScanKey         rs_key;
} HeapScanDescData;

typedef struct IndexScanDescData {
  Relation        relation;
  void            *opaque;
  ItemPointerData previousItemData;
  ItemPointerData currentItemData;
  ItemPointerData nextItemData;
  MarkData        previousMarkData;
  MarkData        currentMarkData;
  MarkData        nextMarkData;
  uint8           flags;
  bool            scanFromEnd;
  uint16          memberOfKeys;
  ScanKey         keyData;
} IndexScanDescData;

typedef IndexScanDescData *IndexScanDesc;

typedef HeapScanDescData  *HeapScanDesc;

typedef IndexScanDesc     *IndexScanDescPtr;


#endif
