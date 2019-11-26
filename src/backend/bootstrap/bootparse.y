%{
#include "access/xact.h"
#include "bootstrap/bootstrap.h"

#define DO_START {StartTransactionCommand();}

#define DO_END {CommitTransactionCommand();\
  if(!Quiet){ EMITPROMPT}\
  fflush(stdout);\
 }

%}

%union {
  int ival;
}

%type <ival> ident
%type <ival> optbootstrap

%token <ival> ID
%token OPEN XCLOSE XCREATE
%token COMMA EQUALS
%start TopLevel

%nonassoc low
%nonassoc high

%%
TopLevel:
Queries
|
;

Queries:
Query
| Queries Query
;

Query:
OpenStmt
| CloseStmt
| CreateStmt
| InsertStmt
| DeclareIndexStmt
| BuildIndsStmt
;

OpenStmt:
OPEN ident
{
  DO_START;
  boot_openrel(LexIDStr($2));
  DO_END;
}

CloseStmt:
XCLOSE ident %prec low
{
  DO_START;

  DO_END;
}
| XCLOSE %prec high
{
  DO_START;

  DO_END;
}

CreateStmt:
XCREATE optbootstrap ident LPARAN
{
  DO_START;
  numattr = (int)0;
}
typelist
{
  if(!Quiet) putchar('\n');
  DO_END;
}
RPARAN
{
  DO_START;

  if($2) {

  }
}

typelist:
typething
| typelist COMMA typething
;

typething:
ident EQUALS ident
{
  if(++numattr > MAXATTR)
    elog(FATAL, "Too many attributes\n");
  DefineAttr(LexIDStr($1), LexIDStr($3), numattr-1);
  if(DebugMode)
    printf("\n");
}
;

ident:
ID {$$=yylval.ival;}
;


%%
