#ifndef XACT_H
#define XACT_H
#include "miscadmin.h"
#include "utils/nabstime.h"

typedef struct TransactionStateData{
  TransactionId  transactionIdData;
  CommandId      commandId;
  AbsoluteTime   startTime;
  int            state;
  int            blockState;
} TransactionStateData;

#define TRANS_DEFAULT    0
#define TRANS_START      1
#define TRANS_INPROGRESS 2
#define TRANS_COMMIT     3
#define TRANS_ABORT      4
#define TRANS_DISABLED   5

#define TBLOCK_DEFAULT 0

typedef TransactionStateData *TransactionState;

extern void          StartTransaction();
extern void          StorageInvalidTransactionId(TransactionId *destination);
extern TransactionId GetCurrentTransactionId(void);
#endif
