#include "utils/elog.h"

int
smgrcreate(int16 which, Relation reln){
  int fd;

  if((fd = (*(smgrsw[which].smgr_create))(reln)) < 0)
    elog(WARN, "cannot open %.*s", NAMEDATALE, &(reln->rd_rel->relname.data[0]));

  return (fd);
}
