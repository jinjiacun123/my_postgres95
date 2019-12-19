#include "postgres.h"
#include "utils/rel.h"
#include "access/transam.h"

TransactionId NullTransactionId = (TransactionId) 0;
TransactionId AmiTransactionId  = (TransactionId)512;

Relation VariableRelation = (Relation)NULL;
