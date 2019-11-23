#include "postgres.h"
#include "access/transam.h"

void
GetNewTransactionId(TransactionId *xid)
{
  TransactionId nextid;

  if(AMI_OVERRIDE){
    TransactionIdStore(AmiTransactionId, xid);
    return;
  }
}
