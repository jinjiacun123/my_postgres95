#ifndef RELSCAN_H
#define RELSCAN_H

#include "storage/buf.h"
#include "access/htup.h"
#include "utils/rel.h"
#include "utils/tqual.h"

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

typedef HeapScanDescData *HeapScanDesc;
#endif
