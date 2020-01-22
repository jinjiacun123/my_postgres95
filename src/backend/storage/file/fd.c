#include<stdio.h>
#include "storage/fd.h"
#include "utils/elog.h"


#define DO_DB(A) /* A */
#define FileIsNotOpen(file) (VfdCache[file].fd == VFD_CLOSED)
#define FD_DIRTY  (1 << 0)
#define VFD_CLOSED -1
typedef struct vfd {
  signed   short fd;
  unsigned short fdstate;
  File           nextFree;
  File           lruMoreRecently;
  long           seekPos;
  char           *fileName;
  int            fileFlags;
  int            fileMode;
} Vfd;

static Vfd    *VfdCache;
static int    FreeFd = 0;
static int    nfile = 0;

static int FileAccess(File file);
static char * filepath(char *filename);
static File fileNameOpenFile(FileName  fileName,
                             int       fileFlags,
                             int       fileMode);
static void Delete(File file);
static void FreeVfd(File file);

long
FileSeek(File file, long offset, int whence){
  int returnCode;

  DO_DB(printf("DEBUG: FileSeek:%d (%s) %d %d\n", file, VfdCache[file].fileName, offset, whence));

  if(FileIsNotOpen(file)){
    switch(whence){
    case SEEK_SET:
      VfdCache[file].seekPos = offset;
      return offset;
    case SEEK_CUR:
      VfdCache[file].seekPos = VfdCache[file].seekPos + offset;
      return VfdCache[file].seekPos;
    case SEEK_END:
      FileAccess(file);
      returnCode = VfdCache[file].seekPos
        = lseek(VfdCache[file].fd, offset, whence);
      return returnCode;
    default:
      elog(WARN, "FileSeek: invalid whence: %d", whence);
      break;
    }
  } else {
    returnCode = VfdCache[file].seekPos
      = lseek(VfdCache[file].fd, offset, whence);
    return returnCode;
  }

  return (-1L);
}

File
FileNameOpenFile(FileName fileName,
                 int      fileFlags,
                 int      fileMode){
  File   fd;
  char   *fname;

  fname  = filepath(fileName);
  fd     = fileNameOpenFile(fname, fileFlags, fileMode);
  pfree(fname);
  return(fd);
}

int
FileRead(File  file,
         char  *buffer,
         int   amount){
  int    returnCode;

  DO_DB(printf("DBBUG: FileRead: %d (%s) %d 0x%x\n",
               file,
               VfdCache[file].fileName,
               amount,
               buffer));
  FileAccess(file);
  returnCode = read(VfdCache[file].fd, buffer, amount);
  if(returnCode > 0){
    VfdCache[file].seekPos += returnCode;
  }

  return returnCode;
}

int
FileWrite(File  file,
          char  *buffer,
          int    amount){
  int  returnCode;

  DO_DB(printf("DB: FileWrite: %d (%s) %d 0x%lx\n",
               file,
               VfdCache[file].fileName,
               amount,
               buffer));
  FileAccess(file);
  returnCode = write(VfdCache[file].fd, buffer, amount);
  if(returnCode > 0){
    VfdCache[file].seekPos += returnCode;
  }

  VfdCache[file].fdstate |= FD_DIRTY;

  return(returnCode);
}


void
FileClose(File file){
  int returnValue;

  DO_DB(printf("DEBUG: FileClose: %d (%s)\n",
               file,
               VfdCache[file].fileName));

  if(!FileIsNotOpen(file)){
    Delete(file);
    FreeFd++;
    if(VfdCache[file].fdstate & FD_DIRTY){
      returnValue = fsync(VfdCache[file].fd);
      Assert(returnValue != -1);
      VfdCache[file].fdstate &= ~FD_DIRTY;
    }

    returnValue = close(VfdCache[file].fd);
    Assert(returnValue != -1);
    --nfile;
    VfdCache[file].fd = VFD_CLOSED;
  }
  FreeVfd(file);
  free(VfdCache[file].fileName);
}

int
FileNameUnlink(char *filename){
  int  retval;
  char *fname;

  fname  = filepath(filename);
  retval = unlink(fname);
  pfree(fname);
  return(retval);
}

int
FileSync(File file){
  int returnCode;

  return(returnCode);
}

File
PathNameOpenFile(FileName fileName,
                 int      fileFlags,
                 int      fileMode){
  return(fileNameOpenFile(fileName, fileFlags, fileMode));
}


static int
FileAccess(File file){
  int returnValue;

  return(0);
}

static char *
filepath(char *filename){
  char *buf;

  return(buf);
}

static File
fileNameOpenFile(FileName  fileName,
                 int       fileFlags,
                 int       fileMode){
  File file;

  return(file);
}

static void
Delete(File file){

}

static void
FreeVfd(File file){

}
