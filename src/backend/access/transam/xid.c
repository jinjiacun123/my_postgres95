#include "postgres.h"

void
TransactionIdStore(TransactionId transactionId,
                   TransactionId *destination)
{
  *destination = transactionId;
}
