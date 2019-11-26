#include "access/xact.h"
#include "postgres.h"

bool AMI_OVERRIDE = false;

TransactionStateData CurrentTransactionStateData = {
  0,
  FirstCommandId,
  0x0,
  TRANS_DEFAULT,
  TBLOCK_DEFAULT
};
TransactionState CurrentTransactionState = &CurrentTransactionStateData;

void
StartTransactionCommand()
{
  TransactionState s = CurrentTransactionState;

  switch(s->blockState){
  case TBLOCK_DEFAULT:
    StartTransaction();
  }
}

void
StartTransaction()
{
  TransactionState s = CurrentTransactionState;

  if(s->state == TRANS_DISABLED || s->state == TRANS_INPROGRESS)
    return;

  s->state = TRANS_START;

  GetNewTransactionId(&(s->transactionIdData));

  s->commandId = FirstCommandId;
  s->startTime = GetCurrentAbsoluteTime();

  AtStart_Cache();
  //AtStart_Locks();
  //AtStart_Memory();


  //InitTempRelList();

  s->state = TRANS_INPROGRESS;
}

void
AtStart_Cache(){
  DiscardInvalid();
}

void
CommitTransactionCommand(){

}
