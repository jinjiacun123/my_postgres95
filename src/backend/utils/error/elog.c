#include<stdio.h>
#include<stdarg.h>
#include<time.h>
#include "utils/elog.h"

static int Debugfile = -1;
static int ElogDebugIndentLevel = 0;

void
elog(int lev, char *fmt, ...)
{
  va_list  ap;
  char     buf[ELOG_MAXLEN], line[ELOG_MAXLEN];
  register char *bp, *cp;
  extern   int errno, sys_nerr;
  time_t   tim, time();
  int      len;
  int      i = 0;

  va_start(ap, fmt);
  if(lev == DEBUG && Debugfile < 0){
    return ;
  }

  switch(lev){
  case NOIND:
    i = ElogDebugIndentLevel-1;
    if(i < 0) i = 0;
    if(i > 30) i = i%30;
    cp = "DEBUG:";
    break;
  case DEBUG:
    i = ElogDebugIndentLevel-1;
    if(i < 0) i = 0;
    if(i > 30) i = i % 30;
    cp = "DEBUG:";
    break;
  case NOTICE:
    cp = "NOTICE:";
    break;
  case WARN:
    cp = "WARN:";
    break;
  default:
    sprintf(line, "FATAL %d:", lev);
    cp = line;
  }












}
