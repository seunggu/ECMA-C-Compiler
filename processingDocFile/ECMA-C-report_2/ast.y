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

%token SIZEOF FUNC VAR STRUCT IF ELSE WHILE FOR CONTINUE BREAK RETURN
%token INC_OP DEC_OP LE_OP GE_OP AND_OP OR_OP EQ_OP NE_OP PTR_OP 
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN 
%token <sval> IDENTIFIER STRING_LITERAL
%token <ival> INT_LITERAL BOOLEAN_LITERAL
%token <dval> DOUBLE_LITERAL

%start Translation_Unit
%%

// part1: 프로그램 선언

// 됨
Translation_Unit
    : External_Decl
    | Translation_Unit External_Decl
    ;

// 됨
External_Decl
    : Declaration
    | Func_Definition
    ;







// part2: 변수 선언

// 됨
Declaration 
    : Declaration_Specifiers ';'
    | Declaration_Specifiers Init_Declarator_List ';'
    ;

// 됨 (struct 빠짐)
Declaration_Specifiers
    : VAR
    ;

// 됨
Init_Declarator_List
    : Init_Declarator
    | Init_Declarator_List ',' Init_Declarator
    ;

// 됨
Init_Declarator
    : Declarator
    | Declarator '=' Assign_Exp
    ;

// 됨
Declarator
    : Pointer Direct_Declarator
    | Direct_Declarator
    ;

// 됨
Pointer
    : '*'
    | '*' Pointer
    ;
 
// 됨
Direct_Declarator
    : IDENTIFIER
    | '(' Declarator ')'
    ;







// part3: 각종 Exp 정리

// 됨
Primary_Exp
    : IDENTIFIER
    | INT_LITERAL
    | DOUBLE_LITERAL
    | STRING_LITERAL
    | BOOLEAN_LITERAL
    | List_Literal
    ;

// 됨
List_Literal
    : '[' Primary_Exp_List ']'
    | '[' ']'
    ;

// 됨
Primary_Exp_List
    : Primary_Exp
    | Primary_Exp_List ',' Primary_Exp
    ;

// 됨
Exp
    : Assign_Exp
    | Exp ',' Assign_Exp
    ;

// 됨
Assign_Exp
    : Conditional_Exp
    | Unary_Exp Assign_Op Assign_Exp

// 됨
Assign_Op   
    : '='
    | ADD_ASSIGN
    | SUB_ASSIGN
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    ;

//진행 중...

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
}
