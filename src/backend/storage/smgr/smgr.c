#include "postgres.h"
#include "utils/elog.h"
#include "utils/rel.h"
#include "storage/smgr.h"

typedef struct f_smgr {
  int (*smgr_init)();
  int (*smgr_shutdown)();
  int (*smgr_create)();
  int (*smgr_unlink)();
  int (*smgr_extend)();
  int (*smgr_open)();
  int (*smgr_close)();
  int (*smgr_read)();
  int (*smgr_write)();
  int (*smgr_fulsh)();
  int (*smgr_blindwrt)();
  int (*smgr_nblocks)();
  int (*smgr_commit)();
  int (*smgr_abort)();
} f_smgr;

static f_smgr smgrsw[] = {
  {mdinit, NULL,    mdcreate, mdunlink,   mdextend,  mdopen,   mdclose,
   mdread, mdwrite, mdflush,  mdblindwrt, mdnblocks, mdcommit, mdabort },
};

int
smgrcreate(int16 which, Relation reln){
  int fd;

  if((fd = (*(smgrsw[which].smgr_create))(reln)) < 0)
    elog(WARN, "cannot open %.*s", NAMEDATALEN, &(reln->rd_rel->relname.data[0]));

  return (fd);
}

int
smgropen(int16 which, Relation reln){
  int fd;

  if((fd = (*(smgrsw[which].smgr_open))(reln)) < 0)
    elog(WARN, "cannot open %.*s", NAMEDATALEN, &(reln->rd_rel->relname.data[0]));

  return (fd);
}

int
smgrextend(int16    which,
           Relation reln,
           char     *buffer){
  int status;

  status = (*(smgrsw[which].smgr_extend))(reln, buffer);

  if(status == SM_FAIL)
    elog(WARN, "%.*s: cannot extend",
         NAMEDATALEN,
         &(reln->rd_rel->relname.data[0]));

  return(status);
}

int
smgrread(int16       which,
         Relation    reln,
         BlockNumber blocknum,
         char        *buffer){
  int status;

  status = (*(smgrsw[which].smgr_read))(reln, blocknum, buffer);

  if(status == SM_FAIL)
    elog(WARN, "cannot read block %d of %.*s",
         blocknum,
         NAMEDATALEN,
         &(reln->rd_rel->relname.data[0]));

  return status;
}

int
smgrnblocks(int16    which,
            Relation reln){
  int nblocks;

  if( (nblocks = (*(smgrsw[which].smgr_nblocks))(reln)) < 0)
    elog(WARN, "cannot count blocks for %.*s",
         NAMEDATALEN,
         &(reln->rd_rel->relname.data[0]));

  return (nblocks);
}
