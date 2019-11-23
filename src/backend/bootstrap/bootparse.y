%{
#include "access/xact.h"

#define DO_START {StartTransactionCommand();}



%}

%union {
  int ival;
}

%type <ival> ident

%token <ival> ID
%token OPEN
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
;

OpenStmt:
OPEN ident
{
  DO_START;
  //boot_openrel(LexIDStr($2));
  //DO_END;
}

ident:
ID {$$=yylval.ival;}
;


%%
