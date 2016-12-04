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
    | Constant
    | STRING_LITERAL
    | BOOLEAN_LITERAL
    | Func_Definition
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
Constant
    : INT_LITERAL
    | DOUBLE_LITERAL
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

// 됨
Conditional_Exp    
    : Logical_Or_Exp
    | Logical_Or_Exp '?' Exp ':' Conditional_Exp
    ;

// 됨
Logical_Or_Exp    
    : Logical_And_Exp
    | Logical_Or_Exp OR_OP Logical_And_Exp
    ;

// 됨
Logical_And_Exp     
    : Equal_Exp
    | Logical_And_Exp AND_OP Equal_Exp
    ;

// 됨
Equal_Exp          
    : Rational_Exp
    | Equal_Exp EQ_OP Rational_Exp
    | Equal_Exp NE_OP Rational_Exp
    ;

// 됨
Rational_Exp    
    : Addtive_Exp
    | Rational_Exp '<' Addtive_Exp
    | Rational_Exp '>' Addtive_Exp
    | Rational_Exp LE_OP Addtive_Exp
    | Rational_Exp GE_OP Addtive_Exp
    ;

// 됨
Addtive_Exp     
    : Multiple_Exp
    | Addtive_Exp '+' Multiple_Exp
    | Addtive_Exp '-' Multiple_Exp
    ;

// 됨
Multiple_Exp
    : Unary_Exp
    | Multiple_Exp '*' Unary_Exp
    | Multiple_Exp '/' Unary_Exp
    | Multiple_Exp '%' Unary_Exp
    ;

// 됨
Unary_Exp
    : Postfix_Exp
    | INC_OP Unary_Exp
    | DEC_OP Unary_Exp
    | Unary_Op Unary_Exp
    | SIZEOF Unary_Exp
    ;

// 됨
Unary_Op
    : '&'
    | '*'
    | '+'
    | '-'
    | '!'
    ;

// 됨
Postfix_Exp
    : Primary_Exp
    | Postfix_Exp '[' Exp ']'
    | Postfix_Exp PTR_OP IDENTIFIER
    | Postfix_Exp INC_OP
    | Postfix_Exp DEC_OP
    ;






// part4. 함수 선언

// 됨
Func_Definition
    : FUNC Func_Declarator Compound_Statement
    ;

// 됨
Func_Declarator
    : IDENTIFIER '(' Identifier_List ')'
    | IDENTIFIER '(' ')'
    | '(' Identifier_List ')'
    | '(' ')' 
    ;

// 됨
Identifier_List
    : IDENTIFIER
    | Identifier_List ',' IDENTIFIER
    ;





// part5. Statement 선언

// 됨
Statement
    : Compound_Statement
    | Exp_Statement
    | Selection_Statement
    | Iteration_Statement
    | Jump_Statement
    ;

// 됨
Compound_Statement
    : '{' '}'
    | '{' Statement_List '}'
    | '{' Declaration_List '}'
    | '{' Declaration_List Statement_List '}'
    ;

//  됨
Declaration_List 
    : Declaration
    | Declaration_List Declaration
    ;

// 됨
Statement_List
    : Statement
    | Statement_List Statement
    ;

// 됨
Exp_Statement
    : ';'
    | Exp ';'
    ;

// 됨
Selection_Statement
    : Matched
    | UnMatched
    ;

// 됨
Matched
    : IF '(' Exp ')' Matched ELSE Matched
    ;

// 됨
UnMatched
    : IF '(' Exp ')' Statement
    | IF '(' Exp ')' Matched ELSE UnMatched
    ;

// 됨
Iteration_Statement
    : WHILE '(' Exp ')' Statement
    | FOR '(' Exp_Statement Exp_Statement ')' Statement
    | FOR '(' Exp_Statement Exp_Statement Exp ')' Statement
    ;

// 됨
Jump_Statement
    : CONTINUE ';'
    | BREAK ';'
    | RETURN ';'
    | RETURN Exp ';'
    ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
}
