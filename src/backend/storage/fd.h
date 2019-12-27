#ifndef FD_H
#define FD_H
#include "c.h"
#include "storage/block.h"

typedef char *FileName;

typedef int  File;

extern File FileNameOpenFile(FileName fileName,
                             int      fileFlags,
                             int      fileMode);
extern int  FileRead(File    file,
                     char    *buffer,
                     int     amount);
extern int  FileWrite(File   file,
                      char   *buffer,
                      int    amount);
extern void FileClose(File file);
extern int  FileNameUnlink(char *filename);
extern long FileSeek(File  file,
                     long  offset,
                     int   whence);






#endif
