%{  // Flex input
    #include <stdlib.h>
    #include "exp.h"
    #include "y.tab.h"
%}
oper         [\- | \+ | \* | \/ | \% | \+\+ | \-\- | \! | \& | \< | \> | \<\= | />/= | /&/& | /|/| | /=/= | /= | \!\= | /+/= | /-/= | /*/= | ///= | /%/=]
variable     [_]*[a-zA-Z]{1}[a-zA-Z0-9_]*
interger     [0-9]+
double       [integer(.integer)]
string       [\".\"]
bool         [TRUE | FALSE]
%%
{oper}       { return(yytext[0]); }
{integer}	   { yylval.ival = atoi(yytext); return(INT); }
{double}     { yylval.dval = atoi(yytext); return(DBL); }
{variable}   { yylval.sval = yytext; return(ID); }
{string}     { yylval.sval = yytext; return(STR); }
{bool}       { yylval.bval = yytext; return(BOOL); }
"("          { return '('; }
")"          { return ')'; }
"["          { return '['; }
"]"          { return ']'; }
"sizeof"     { return 'sizeof'; }
[ \t\r]	;
\n	         { return(0); }
.	           { printf("'%c': illegal character\n", yytext[0]); exit(-1); }
%%
int yywrap() { return 1; }
