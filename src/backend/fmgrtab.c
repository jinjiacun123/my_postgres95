/*-------------------------------------------------------------------------
 *
 * fmgrtab.c--
 *    The function manager's table of internal functions.
 *
 * Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *    : /usr/local/cvsroot/postgres95/src/backend/utils/Gen_fmgrtab.sh,v 1.3 1996/07/22 21:55:40 scrappy Exp $
 *
 * NOTES
 *
 *	******************************
 *	*** DO NOT EDIT THIS FILE! ***
 *	******************************
 *
 *	It has been GENERATED by /home/jim/source_code/my_postgres95/src/backend/utils/Gen_fmgrtab.sh
 *	from /home/jim/source_code/my_postgres95/src/backend/catalog/pg_proc.h
 *
 *	We lie here to cc about the return type and arguments of the
 *	builtin functions; all ld cares about is the fact that it
 *	will need to resolve an external function reference.
 *
 *-------------------------------------------------------------------------
 */
#ifdef WIN32
#include <limits.h>
#else
# if defined(PORTNAME_BSD44_derived) ||      defined(PORTNAME_bsdi) ||      defined(PORTNAME_bsdi_2_1)
# include <machine/limits.h>
# define MAXINT	INT_MAX
# else
# include <values.h>           /* for MAXINT */
# endif /* bsd descendents */
#endif /* WIN32 */

#include "utils/fmgrtab.h"

extern char *boolin();
extern char *boolout();
extern char *textout();

static FmgrCall fmgr_builtins[] = {
  {28 , 1 , boolin, "boolin" },
  {29 , 1 , boolout, "boolout" },
  {47 , 1 , textout, "textout" },
	/* guardian value */
#ifndef WIN32
      { MAXINT, 0, (func_ptr) NULL }
#else
      { INT_MAX, 0, (func_ptr) NULL }
#endif /* WIN32 */
};

static int fmgr_nbuiltins = (sizeof(fmgr_builtins) / sizeof(FmgrCall)) - 1;

FmgrCall *fmgr_isbuiltin(Oid id)
{
    register int i;
    int	low = 0;
    int	high = fmgr_nbuiltins;

    low = 0;
    high = fmgr_nbuiltins;
    while (low <= high) {
	i = low + (high - low) / 2;
	if (id == fmgr_builtins[i].proid)
	    break;
	else if (id > fmgr_builtins[i].proid)
	    low = i + 1;
	else
	    high = i - 1;
    }
    if (id == fmgr_builtins[i].proid)
	return(&fmgr_builtins[i]);
    return((FmgrCall *) NULL);
}

func_ptr fmgr_lookupByName(char *name)
{
    int i;
    for (i=0;i<fmgr_nbuiltins;i++) {
	if (strcmp(name,fmgr_builtins[i].funcName) == 0)
		return(fmgr_builtins[i].func);
    }
    return((func_ptr) NULL);
}

