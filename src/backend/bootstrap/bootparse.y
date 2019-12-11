%{
#include "access/xact.h"
#include "access/tupdesc.h"
#include "bootstrap/bootstrap.h"
#include "storage/smgr.h"

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
%token COMMA EQUALS LPAREN RPAREN XBOOTSTRAP
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
CreateStmt
;

//Query:
//OpenStmt
//| CloseStmt
//| CreateStmt
//;

//OpenStmt:
//OPEN ident
//{
//  DO_START;
//  boot_openrel(LexIDStr($2));
//  DO_END;
//}
//;

//CloseStmt:
//XCLOSE ident %prec low
//{
//  DO_START;

//  DO_END;
//}
//| XCLOSE %prec high
//{
//  DO_START;

//  DO_END;
//}
//;

CreateStmt:
XCREATE optbootstrap ident LPAREN
{
  DO_START;
  numattr = (int)0;
}
typelist
{
  DO_END;
}
RPAREN
{
  DO_START;
  if($2) {
    extern Relation reldesc;
    TupleDesc       tupdesc;

    if(reldesc){
      puts("create bootstrap: Warning,open relation");
      puts("exists, closing first");
      closerel(NULL);
    }

    tupdesc = CreateTupleDesc(numattr, attrtypes);
    reldesc = heap_creatr(LexIDStr($3), DEFAULT_SMGR, tupdesc);
  }
}
;

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
}
;

optbootstrap:
XBOOTSTRAP {$$ = 1;}
| { $$ = 0;}
;

ident:
ID {$$=yylval.ival;}
;


%%
