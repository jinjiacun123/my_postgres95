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
