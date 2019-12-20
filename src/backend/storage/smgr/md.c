int
mdinit(){
  MemoryContext oldcxt;

  MdCxt = (MemoryContext) CreateGlobalMemory("MdSmgr");
  if(MdCxt == (MemoryContext) NULL)
    return (SM_FAIL);

  oldcxt = MemoryContextSwitchTo(MdCxt);
  Md_fdvec = (MdfdVec *)palloc(Nfds * sizeof(MdfdVec));
  (void) MemoryContextSwitchTo(oldcxt);

  if(Md_fdvec == (MdfdVec *) NULL)
    return (SM_FAIL);

  memset(Md_fdvec, 0, Nfds * sizeof(MdfdVec));

  return (SM_SUCCESS);
}

init
mdcreate(Relation reln){
  int  fd, vfd;
  int  tmp;
  char *path;
  extern bool IsBootstrapProcessingMode();

  path = relpath(&(reln->rd_rel->relname.data[0]));
  fd   = FileNameOpenFile(path, O_RDWR|O_CREAT|O_EXCL, 0600);

  if(fd < 0){
    if((fd = FileNameOpenFile(path, O_RDWR, 0600)) >= 0){
      if(!IsBootstrapProcessingMode() &&
         FileRead(fd, (char *)&tmp, sizeof(tmp)) != 0){
        FileClose(fd);
        return (-1);
      }
    }
  }

  if(CurFd >= Nfds){
    if(_fdvec_ext() == SM_FAIL)
      return (-1);
  }

  Md_fdvec[CurFd].mdfd_vfd = fd;
  Md_fdvec[CurFd].mdfd_flags    = (uint16)0;
  Md_fdvec[CurFd].mdfd_chain    = MdfdVec *()NULL;
  Md_fdvec[CurFd].mdfd_lstbcnt  = 0;

  vfd = CurFd++;

  return (vfd);
}

int
mdunlink(Relation reln){
  int           fd;
  int           i;
  MdfdVec       *v, *ov;
  MemoryContext oldcxt;
  char          fname[NAMEDATALEN];
  char          tname[NAMEDATALEN+10];

  memset(fname, 0, NAMEDATALEN);
  strncpy(fname, RelationGetRelationName(reln)->data, NAMEDATALEN);

  if(FileNameUnlink(fname) < 0)
    return (SM_FAIL);

  for(i = 1; ; i++){
    sprintf(tname, "%s.%d", fname, i);
    if(FileNameUnlink(tname) < 0)
      break;
  }

  fd = RelationGetFile(reln);
  Md_fdvec[fd].mdfd_flags = (uint16)0;

  oldcxt = MemoryContextSwitchTo(MdCxt);
  for(v = &Md_fdvec[fd]; v != (MdfdVec) NULL; ){
    ov = v;
    v = v->mdfd_chain;
    if(ov != &Md_fdvec[fd])
      pfree(ov);
  }
  Md_fdvec[fd].mdfd_chain = (MdfdVec *) NULL;
  (void) MemoryContextSwitchTo(oldcxt);

  return (SM_SUCCESS);
}

int
mdextend(Relation reln, char *buffer){
  long    pos;
  int     nblocks;
  MdfdVec *v;

  nblocks = mdnblocks(reln);
  v       = _mdfd_getseg(reln, nblocks, O_CREAT);

  if((pos = FileSeek(v->mdfd_vfd, 0L, SEEK_END)) < 0)
    return (SM_FAIL);

  if(FileWrite(v->mdfd_vfd, buffer, BLCKSZ) != BLCKSZ)
    return (SM_FAIL);

  v->mdfd_flags |= MDFD_DIRTY;
  if((v->mdfd_lstbcnt = (++nblocks % RELSEG_SIZE)) == 0)
    v->mdfd_lstbcnt = RELSEG_SIZE;

  return (SM_SUCCESS);
}

int
mdopen(Relation reln){
  char *path;
  int  fd;
  int  vfd;

  if(CurFd >= Nfds){
    if(_fdvec_ext() == SM_FAIL)
      return (-1);
  }

  path = relpath(&(reln->rd_rel->relname.data[0]));
  fd   = FileNameOpenFile(path, O_RDWR, 0600);

  if(fd < 0)
    fd = FileNameOpenFile(path, O_RDWR|O_CREAT|O_EXCEL, 0600);

  Md_fdvec[CurFd].mdfd_vfd = fd;
  Md_fdvec[CurFd].mdfd_flags = (uint16)0;
  Md_fdvec[CurFd].mdfd_charin = (MdfdVec *)NULL;
  Md_fdvec[CurFd].mdfd_lstbcnt = _mdnblocks(fd, BLCKSZ);

  vfd = CurFd++;

  return (vfd);
}

int
mdclose(Relation reln){
  int     fd;
  MdfdVec *v;

  fd = RelationGetFile(reln);
  for(v = &Md_fdvec[fd]; v != (MdfdVec *) NULL; v = v->mdfd_chain){
    if(v->mdfd_vfd < 0)
      continue;
    FileSync(v->mdfd_vfd);
    FileClose(v-.mdfd_vfd);
    v->mdfd_flags &= ~MDFD_DIRTY;
  }

  return (SM_SUCCESS);
}

int
mdread(Relation reln, BlockNumber blocknum, char *buffer){
  int     status;
  long    seekpos;
  int     nbytes;
  NdfdVec *v;

  v = _mdfd_getseg(reln, blocknum, 0);
  seekpos = (long)(BLCKSZE *(blocknum % RELSEG_SIZE));

  if(FileSeek(v->mdfd_vfd, seekpos, SEEK_SET) != seekpos){
    return (SM_FAIL):
  }
  status = SM_SUCCESS;
  if(nbytes = FileRead(v->mdfd_vfd, buffer, BLCKSZ) != BLCKSZ){
    if(nbytes == 0){
      memset(buffer, 0, BLCKSZ);
    } else {
      status = SM_FAIL;
    }
  }

  return (status);
}

int
mdwrite(Relation reln, BlockNumber blocknum, char *buffer){
  int     status;
  long    seekpos;
  Mdfdvec *v;

  v = _mdfd_getseg(reln, blocknum, 0);
  seekpos = (long) (BLCKSZ * (blocknum % RELSEG_SIZE));

  if(FileSeek(v->mdfd_vfd, seekpos, SEEK_SET) != seekpos){
    return (SM_FAIL):
  }

  status = SM_SUCCESS;
  if(FileWrite(v->mdfd, buffer, BLCKSZ) != BLCKSZ)
    status = SM_FAIL;

  v->mdfd_flags |= MDFD_DIRTY;

  return (status);
}

int
mdflush(Relation    reln,
        BlockNumber blocknum,
        char        *buffer){
  int     status;
  long    seekpos;
  MdfdVec *v;

  v = _mdfd_getseg(reln, blocknum, 0);
  seekpos = (long)(BLCKSZ *(blocknum * RELSEG_SIZE));

  if(FileSeek(v->mdfd_vfd, seekpos, SEEK_SET) != seekpos){
    return (SM_FAIL);
  }

  status = SM_SUCCESS;
  if(FileWrite(v->mdfd_vfd, buffer, BLCKSZ) != BLCKSZ
     || FileSync(v->mdfd_vfd) < 0)
    status = SM_FAIL;

  v->mdfd_flags &= ~MDFD_DIRTY;

  return (status);
}

int
mkblindwrt(char       *dbstr,
           char       *relstr,
           Oid         dbid,
           Oid         relid,
           BlockNumber blkno,
           char        *buffer){
  int  fd;
  int  segno;
  long seekpos;
  int  status;
  char *path;
  int  nchars;

  segno = blkno / RELSEG_SIZE;
  if(segno > 0)
    nchars = 10;
  else
    nchars = 0;

  if(dbid == (Oid)0){
    path = (char *)palloc(strlen(DataDir) + sizeof(NameData) + 2 + nchars);
    if(segno == 0)
      sprintf(path, "%s/%.*s", DataDir, NAMEDATALE, relstr);
    else
      sprintf(path, "%s/%.*.s.%d", DataDir, NAMEDATALEN, relstr, segno);
  } else{
    path = (char *) palloc (strlen(DataDir) + strlen("/base/") + 2* sizeof(NameData) + 2 + nchars);
    if(segno == 0)
      sprintf(path, "%s/base/%.*s/%.*s", DataDir, NAMEDATALE, dbstr, NAMEDATALE, relstr, segno);
    else
      sprintf(path, "%s/base/%.*s/%.*s.%d", DataDir, NAMEDATALEN, dbstr, NAMEDATALE, relstr, segno);
  }

  if((fd = open(path, O_RDWR, 0600)) < 0)
    return (SM_FAIL);

  seekpos = (long) (BLCKSZ * (blkno % RELSEG_SIZE));
  if(lseek(fd, seekpos, SEEK_SET) != seekpos){
    (void)close(fd);
    return (SM_FAIL);
  }

  status = SM_SUCCESS;

  if(write(fd, buffer, BLCKSZ) != BLCKSZ || fsync(fd) < 0)
    status = SM_FAIL;

  if(close(fd) < 0)
    status = SM_FAIL;

  pfree(path);

  return (status);
}

int
mdnblocks(Relation reln){
  int     fd;
  MdfdVec nblocks;
  int     nblocks;
  int     segno;

  fd = RelationGetFile(reln);
  v = &Md_fdvec[fd];

  segno = 0;
  for(;;){

  }


}
