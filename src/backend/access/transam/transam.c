#include "postgres.h"
#include "utils/rel.h"
#include "access/transam.h"

TransactionId AmiTransactionId = (TransactionId)512;

Relation VariableRelation = (Relation)NULL;
