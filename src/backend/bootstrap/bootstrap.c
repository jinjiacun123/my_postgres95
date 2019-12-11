#include<string.h>
#include "bootstrap/bootstrap.h"
#include "fmgr.h"
#include "catalog/pg_type.h"

#define STRTABLESIZE  10000
#define HASHTABLESIZE 503

char     *strtable[STRTABLESIZE];
hashnode *hashtable[HASHTABLESIZE];
static   int strtable_end = -1;

#define NUM     23
#define NUMSQR  529
#define NUMCUBE 12167

struct typmap {
  Oid               am_oid;
  TypeTupleFormData am_typ;
};

static struct typmap **Typ = (struct typmap **)NULL;

AttributeTupleForm   attrtypes[MAXATTR];
int                  numattr;


Relation    reldesc;
static char *relname;

struct typinfo {
  char  name[NAMEDATALEN];
  Oid   oid;
  Oid   elem;
  int16 len;
  Oid   inproc;
  Oid   outproc;
};

static struct typinfo Procid[] = {
  {"bool", 16, 0, 1, F_BOOLIN, F_BOOLOUT}
};

static int n_types = sizeof(Procid)/ sizeof(struct typinfo);


int
BootstrapMain(int argc, char *argv[])
{
	Int_yyparse();
	return 0;
}

int
EnterString(char *str)
{
  hashnode *node;
  int       len;

  len = strlen(str);

  node = FindStr(str, len, 0);
  if(node){
    return (node->strnum);
  } else {
    node = AddStr(str, len, 0);
    return (node->strnum);
  }

  return 0;
}

hashnode *
FindStr(char *str, int length, hashnode *mderef)
{
  hashnode *node;
  node = hashtable[CompHash(str, length)];
  while(node != NULL){
    if(!strcmp(str, strtable[node->strnum])){
      return (node);
    } else {
      node = node->next;
    }
  }

  return (NULL);
}

hashnode *
AddStr(char *str, int strlength, int mderef)
{
  hashnode *temp, *trail, *newnode;
  int      hashresult;
  int      len;

  if(++strtable_end == STRTABLESIZE){
    elog(FATAL, "There are too many string constructs and identifiers for the compiler to handle.");
  }

  if((len = strlength -1) < NAMEDATALEN)
    len = NAMEDATALEN;

  strtable[strtable_end] = malloc((unsigned) len);
  strcpy(strtable[strtable_end], str);

  newnode         = (hashnode*)malloc(sizeof(hashnode)*1);
  newnode->strnum = strtable_end;
  newnode->next   = NULL;

  hashresult = CompHash(str, strlength);
  if(hashtable[hashresult] == NULL){
    hashtable[hashresult] = newnode;
  } else {
    trail = hashtable[hashresult];
    temp = trail->next;
    while(temp != NULL){
      trail = temp;
      temp  = temp->next;
    }
    trail->next = newnode;
  }

  return (newnode);
}

int
CompHash(char *str, int len)
{
  register int result;
  result = (NUM * str[0] + NUMSQR * str[len-1] + NUMCUBE * str[(len -1)/2]);

  return (result % HASHTABLESIZE);
}

void
boot_openrel(char *relname)
{
  int i;
  struct typmap **app;
  Relation      rdesc;
  HeapScanDesc  sdesc;

  if(strlen(relname) > 15)
    relname[15] = '\000';
}

char *
LexIDStr(int ident_num)
{
  return (strtable[ident_num]);
}

void
DefineAttr(char *name, char *type, int attnum)
{
  int attlen;
  int t;

  if(reldesc != NULL){
    fputs("Warning: no open relations allowed with 't' command.\n", stderr);
    closerel(relname);
  }

  t = gettype(type);
}

void
closerel(char *name){

}

int
gettype(char *type)
{
  int           i;
  Relation      rdesc;
  HeapScanDesc  sdesc;
  HeapTuple     tup;
  struct typmap **app;

  if(Typ != (struct typmap *)NULL){

  }
  else
   {
     for(i = 0; i <= n_types; i++){

     }
   }
}
