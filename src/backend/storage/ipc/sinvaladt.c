#include "storage/sinvaladt.h"

SISeg *shmInvalBuffer;


void
SIReadEntryData(SISeg *segP,
                int   backendId,
                void  (*invalFunction)(),
                void  (*resetFunction)())
{

}

void
SIDelExpiredDataEntries(SISeg *segP)
{

}
