%{
#include "bootstrap_token.h"

YYSTYPE yylval;
int yyline;
%}

D [0-9]
oct \\{D}{D}{D}
id ([A-Za-z_]|{oct}|\-)+
%%
open {return(OPEN);}

{id} {
yylval.ival = EnterString(scanstr((char *)yytext));
return (ID);
}
%%

yywrap(){
return 1;
}

yyerror(str)
char *str;
{
fprintf(stderr, "\tsyntax error %d:%s", yyline, str);
}
