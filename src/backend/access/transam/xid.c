#include "postgres.h"

extern TransactionId NullTransactionId;

void
TransactionIdStore(TransactionId transactionId,
                   TransactionId *destination)
{
  *destination = transactionId;
}

void
StoreInvalidTransactionId(TransactionId *destination){
  *destination = NullTransactionId;
}

bool
TransactionIdEquals(TransactionId id1,
                    TransactionId id2){
  return ((bool)(id1 == id2));
}
