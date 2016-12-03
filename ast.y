%{  // Bison input
    #include <stdio.h>

    int yylex(void);
    int yyerror(char *msg);
%}
%union {
    char    *sval;
    int      ival;
    double   dval;
}


%token SIZEOF INC_OP DEC_OP LE_OP GE_OP AND_OP OR_OP EQ_OP NE_OP ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN 
%token <sval> IDENTIFIER STRING_LITERAL
%token <ival> INT_LITERAL BOOLEAN_LITERAL
%token <dval> DOUBLE_LITERAL

// type

%right '=' ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%left AND_OP OR_OP
%left EQ_OP NE_OP
%left '<' LE_OP '>' GE_OP
%left '+' '-'
%left '*' '/' '%'
%left POS INC_OP DEC_OP '!' '&' SIZEOF

%%

Primary_Exp : IDENTIFIER
            | INT_LITERAL
            | DOUBLE_LITERAL
            | BOOLEAN_LITERAL
            | STRING_LITERAL
            | '(' Exp ')'
            ;

Postfix_Exp 
    : Primary_Exp
    | Postfix_Exp '[' Exp ']'
    | Postfix_Exp '(' Exp ')'
    | Postfix_Exp '(' Argument_Exp_List ')'
    | Postfix_Exp '.' IDENTIFIER
    | postfix_Exp PTR_OP IDENTIFIER
    | postfix_Exp INC_OP
    | postfix_Exp DEC_OP
    ;

Argument_Exp_List   
    : Assign_Exp
    | Argument_Exp_List ',' Assign_Exp
    ;

Unary_Exp   
    : Postfix_Exp
    | INC_OP Unary_Exp
    | DEC_OP Unary_Exp
    | Unary_Op Unary_Exp
    | SIZEOF Unary_Exp
    ;

Unary_Op
    : '&'
    | '*'
    | '+'
    | '-'
    | '~'
    | '!'
    ;

Multiple_Exp
    : Unary_Exp
    | Multiple_Exp '*' Unary_Exp
    | Multiple_Exp '/' Unary_Exp
    | Multiple_Exp '%' Unary_Exp
    ;

Addtive_Exp     
    : Multiple_Exp
    | Addtive_Exp '+' Multiple_Exp
    | Addtive_Exp '-' Multiple_Exp
    ;

Rational_Exp    
    : Addtive_Exp
    | Rational_Exp '<' Addtive_Exp
    | Rational_Exp '>' Addtive_Exp
    | Rational_Exp LE_OP Addtive_Exp
    | Rational_Exp GE_OP Addtive_Exp
    ;

Equal_Exp          
    : Rational_Exp
    | Equal_Exp EQ_OP Rational_Exp
    | Equal_Exp NE_OP Rational_Exp

    ;

Logical_And_Exp     
    : Equal_Exp
    | Logical_And_Exp AND_OP Equal_Exp
    ;

Logical_Or_Exp    
    : Logical_And_Exp
    | Logical_Or_Exp OR_OP Logical_And_Exp
    ;

Conditional_Exp    
    : Logical_Or_Exp
    | Logical_Or_Exp '?' Exp ':' Conditional_Exp
    ;











Assign_Exp  
    : Conditional_Exp
    | Unary_Exp Assign_Op Assign_Exp
    ;

Assign_Op   
    : '='
    | ADD_ASSIGN
    | SUB_ASSIGN
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    ;

Exp
    : Assign_Exp
    | Exp ',' Assign_Exp
    ;

Constant_Exp
    : Conditional_Exp
    ;

Declaration
    : Declaration_Specifiers ';'
    | Declaration_Specifiers Init_Declarator_List ';'
    ;

Declaration_Specifiers
    | Type_Specifier
    | Type_Specifier Declaration_Specifiers
    | Type_Qualifier
    | Type_Qualifier Declaration_Specifiers
    ;

Init_Declarator_List
    : Init_Declarator
    | Init_Declarator_List ',' Init_Declarator
    ;

Init_Declarator
    : Declarator
    | Declarator '=' Initializer
    ;

Type_Specifier
    : FUNC
    | Struct_Specifier
    ;

Struct_Specifier
    : STRUCT IDENTIFIER '{' Struct_Declaration_List '}'
    | STRUCT '{' Struct_Declaration_List '}'
    | STRUCT IDENTIFIER












Prg : Primary_Exp               { printf("root \n"); };
    ;

Primary_Exp : 

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

Term    : IDENTIFIER        { printf("%s \n", $1); };
        | INT_LITERAL       { printf("%d \n", $1); };
        | DOUBLE_LITERAL    { printf("%lf \n", $1); };
        | STRING_LITERAL    { printf("%s \n", $1); };
        | BOOLEAN_LITERAL   { printf("%d \n", $1); };
        ;
%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
}
