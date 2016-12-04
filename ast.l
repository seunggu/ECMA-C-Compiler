%{  // Flex input
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"

    int GetIntFromBool(char * s);
%}

Letter 		[a-zA-Z_]
Digit		[0-9]
Identifier	{Letter}({Letter}|{Digit})*

%%

"sizeof"	{ return(SIZEOF); }
"func"		{ return(FUNC); }
"var"		{ return(VAR); }
"struct"	{ return(STRUCT); }
"if"		{ return(IF); }
"else"		{ return(ELSE); }
"while"		{ return(WHILE); }
"for"		{ return(FOR); }
"continue" 	{ return(CONTINUE); }
"break"		{ return(BREAK); }
"return"	{ return(RETURN); }

"++"	{ return(INC_OP); }
"--"	{ return(DEC_OP); }
"<="	{ return(LE_OP); }
">="	{ return(GE_OP); }
"&&"	{ return(AND_OP); }
"||"	{ return(OR_OP); }
"=="	{ return(EQ_OP); }
"!="	{ return(NE_OP); }
"+="	{ return(ADD_ASSIGN); }
"-="	{ return(SUB_ASSIGN); }
"*="	{ return(MUL_ASSIGN); }
"/="	{ return(DIV_ASSIGN); }
"%="	{ return(MOD_ASSIGN); }
"->"	{ return(PTR_OP); }

"-"		{ return('-'); }
"+"		{ return('+'); }
"*"		{ return('*'); }
"/"		{ return('/'); }
"%"		{ return('%'); }
"!"		{ return('!'); }
"&"		{ return('&'); }
"<"		{ return('<'); }
">"		{ return('>'); }
"="		{ return('='); }
"("		{ return('('); }
")"		{ return(')'); }
"["		{ return('['); }
"]" 	{ return(']'); }
"," 	{ return(','); }
";"		{ return(';'); }
"?"		{ return('?'); }
":"		{ return(':'); }

{Identifier}		{ yylval.sval = yytext; return(IDENTIFIER); }
{Digit}+			{ yylval.ival = atoi(yytext); return(INT_LITERAL); }
{Digit}+"."{Digit}+	{ yylval.dval = atof(yytext); return(DOUBLE_LITERAL); }
\"(.)*\"			{ yylval.sval = yytext; return(STRING_LITERAL); }
"TRUE"|"FALSE" 		{ yylval.ival = GetIntFromBool(yytext); return(BOOLEAN_LITERAL); }



[ \t\v\n\f]	{ }
.	    	{ printf("'%c': illegal character\n", yytext[0]); exit(-1); }


%%

int yywrap() { return 1; }

int GetIntFromBool(char * s) {
	return strlen(s) == 4 ? 1 : 0;
}