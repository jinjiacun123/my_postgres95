#ifndef SMGR_H
#define SMGR_H

#include "utils/rel.h"

#define SM_FAIL    0
#define SM_SUCCESS 1

#define DEFAULT_SMGR 0

extern int smgrcreate(int16 which, Relation reln);
extern int smgropen(int16 which, Relation reln);
extern int smgrextend(int16    which,
                      Relation reln,
                      char     *buffer);
extern int smgrread(int16       which,
                    Relation    reln,
                    BlockNumber blocknum,
                    char        *buffer);
extern int smgrnblocks(int16    which,
                       Relation reln);

/*in md.c*/
extern int mdinit(void);
extern int mdcreate(Relation reln);
extern int mdunlink(Relation reln);
extern int mdextend(Relation reln, char *buffer);
extern int mdopen(Relation reln);
extern int mdclose(Relation reln);
extern int mdread(Relation reln, BlockNumber blocknum, char *buffer);
extern int mdwrite(Relation reln, BlockNumber blocknum, char *buffer);
extern int mdflush(Relation reln, BlockNumber blocknum, char *buffer);
extern int mdblindwrt(char *dbstr, char *relstr, Oid dbid, Oid relid, BlockNumber blkno, char *buffer);
extern int mdnblocks(Relation reln);
extern int mdcommit(void);
extern int mdabort(void);
#endif
