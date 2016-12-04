%{  // Bison input
    #include <stdio.h>
    #include "exp.h"

    Exp *Root;

    int yylex(void);
    int yyerror(char *msg);
%}
%union {
    char    *sval;
    int      ival;
    double   dval;
    bool     bval;
    Exp     *pval;
}

%token <ival> INT
%token <sval> ID
%token <dval> DBL
%token <sval> STR
%token <bval> BOOL
%type  <pval> Exp

// 우선순위 체크 아직안함

%left '+' '-'
%left '*' '/' '%'
%left NEG




%%
Prg : Exp               { Root = $1; }
    ;
Exp : Exp '+' Exp            { $$ = new BExp('+', $1, $3); }
    | Exp '-' Exp            { $$ = new BExp('-', $1, $3); }
    | Exp '*' Exp            { $$ = new BExp('*', $1, $3); }
    | Exp '/' Exp            { $$ = new BExp('/', $1, $3); }
    | Exp '%' Exp            { $$ = new BExp('%', $1, $3); }
    | Exp '>' Exp            { $$ = new BExp('>', $1, $3); }
    | Exp '<' Exp            { $$ = new BExp('<', $1, $3); }
    | Exp '=' Exp            { $$ = new BExp('=', $1, $3); }
    | Exp '>=' Exp           { $$ = new BExp('>=', $1, $3); }
    | Exp '<=' Exp           { $$ = new BExp('<=', $1, $3); }
    | Exp '!=' Exp           { $$ = new BExp('!=', $1, $3); }
    | Exp '==' Exp           { $$ = new BExp('==', $1, $3); }
    | Exp '||' Exp           { $$ = new BExp('||', $1, $3); }
    | Exp '&&' Exp           { $$ = new BExp('&&', $1, $3); }
    | Exp '%=' Exp           { $$ = new BExp('%=', $1, $3); }
    | Exp '/=' Exp           { $$ = new BExp('/=', $1, $3); }
    | Exp '*=' Exp           { $$ = new BExp('*=', $1, $3); }
    | Exp '-=' Exp           { $$ = new BExp('-=', $1, $3); }
    | Exp '+=' Exp           { $$ = new BExp('+=', $1, $3); }

    | '+' Exp  %prec POS     { $$ = new UNExp('+', $2, 0); }
    | '-' Exp  %prec NEG     { $$ = new UNExp('-', $2, 0); }
    | '&' Exp  %prec REF     { $$ = new UNExp('&', $2, 0); }
    | '*' Exp  %prec PNT     { $$ = new UNExp('*', $2, 0); }
    | '!' Exp  %prec NOT     { $$ = new UNExp('!', $2, 0); }
    | '--' Exp %prec DMN     { $$ = new UNExp('--', $2, 0); }
    | '++' Exp %prec DPL     { $$ = new UNExp('++', $2, 0); }
    | Exp '--' %prec DMN     { $$ = new UNExp('--', $2, 1); }
    | Exp '++' %prec DPL     { $$ = new UNExp('++', $2, 1); }
    | 'sizeof' Exp %prec SIZ { $$ = new UNExp('sizeof', $2); }

    | '(' Exp ')'            { $$ = $2; }
    | '[' Exp ']'            { $$ = $2; }

    | ID                     { $$ = new Id($1); }
    | STR                    { $$ = new Str($1); }
    | BOOL                   { $$ = new Bool($1); }
    | INT                    { $$ = new intNum($1); }
    | DBL                    { $$ = new dblNum($1); }
    ;
%%
int main() {
    yyparse();
    Root->printTree(0);
    return 0;
}
int yyerror(char *s) {
    printf("Error: %s\n", s);
}
