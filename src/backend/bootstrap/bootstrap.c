#include<string.h>
#include "bootstrap/bootstrap.h"

#define STRTABLESIZE  10000
#define HASHTABLESIZE 503

char     *strtable[STRTABLESIZE];
hashnode *hashtable[HASHTABLESIZE];
static   int strtable_end = -1;

#define NUM     23
#define NUMSQR  529
#define NUMCUBE 12167

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
