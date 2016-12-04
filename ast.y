%{  // Bison input
    #include <stdio.h>
    #include "ast.h"

    #define TRUE 1
    #define FALSE 0

    int yylex(void);
    int yyerror(char *msg);
%}
%union {
    char    *sval;
    int      ival;
    double   dval;
    Exp   *expVal;
}

%token SIZEOF FUNC VAR STRUCT IF ELSE WHILE FOR CONTINUE BREAK RETURN
%token INC_OP DEC_OP AND_OP OR_OP EQ_OP NE_OP PTR_OP 
%token <sval> '=' '<' '>'  '&' '*' '+' '-' '!' LE_OP GE_OP 
%token <sval> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN 
%token <sval> IDENTIFIER STRING_LITERAL
%token <ival> INT_LITERAL BOOLEAN_LITERAL
%token <dval> DOUBLE_LITERAL


%type <sval> Assign_Op Unary_Op
%type <expVal> Program Translation_Unit External_Decl Declaration
%type <expVal> Init_Declarator Init_Declarator_List Declarator Direct_Declarator Pointer
%type <expVal> Primary_Exp List_Literal Primary_Exp_List Exp Assign_Exp Conditional_Exp 
%type <expVal> Unary_Exp Logical_Or_Exp Logical_And_Exp Equal_Exp Rational_Exp Addtive_Exp Multiple_Exp Postfix_Exp 


%nonassoc IFX
%nonassoc ELSE

%start Program
%%

// part1: 프로그램 선언

// 됨
Program
    : Translation_Unit                                  { $$ = $1; printTree($$); }
    ;

Translation_Unit
    : External_Decl                                     { $$ = $1; }
    | Translation_Unit External_Decl                    { $$ = new MultiExp($1, $2); }
    ;

// 됨
External_Decl
    : Declaration                                       { $$ = $1; }
    ;







// part2: 변수 선언

// 됨
Declaration 
    : Declaration_Specifiers ';'                        { $$ = new UExp("var", NULL, TRUE); }
    | Declaration_Specifiers Init_Declarator_List ';'   { $$ = new UExp("var", $2, TRUE); }
    ;

// 됨 (struct 빠짐)
Declaration_Specifiers
    : VAR
    ;

// 됨
Init_Declarator_List
    : Init_Declarator                               { $$ = $1; }
    | Init_Declarator_List ',' Init_Declarator      { $$ = new BExp(",", $1, $3); }
    ;

// 됨
Init_Declarator
    : Declarator                            { $$ = $1; }
    | Declarator '=' Assign_Exp             { $$ = new BExp("=", $1, $3); }
    ;

// 됨
Declarator
    : Pointer Direct_Declarator             { $$ = new UExp("*", $2, TRUE); }
    | Direct_Declarator                     { $$ = $1; }
    ;

// 됨
Pointer
    : '*'                                   { $$ = new UExp("*", NULL, TRUE); }
    | '*' Pointer                           { $$ = new UExp("*", $2, TRUE); }
    ;
 
// 됨
Direct_Declarator
    : IDENTIFIER                            { $$ = new Id($1); }
    | '(' Declarator ')'                    { $$ = $2; }
    ;







// part3: 각종 Exp 정리

// 됨
Primary_Exp
    : IDENTIFIER                            { $$ = new Id($1); }
    | INT_LITERAL                           { $$ = new IntNum($1); }
    | DOUBLE_LITERAL                        { $$ = new DbNum($1); }
    | STRING_LITERAL                        { $$ = new Str($1); }
    | BOOLEAN_LITERAL                       { $$ = new Bool($1); }
    | List_Literal                          { $$ = $1; }
    ;

// 됨
List_Literal
    : '[' Primary_Exp_List ']'              { $$ = new ECMAList($2); }
    | '[' ']'                               { $$ = new ECMAList(); }
    ;

// 됨
Primary_Exp_List
    : Primary_Exp                           { $$ = $1; }
    | Primary_Exp_List ',' Primary_Exp      { $$ = new BExp(",", $1, $3); }
    ;

// 됨
Exp
    : Assign_Exp                            { $$ = $1; }
    | Exp ',' Assign_Exp                    { $$ = new BExp(",", $1, $3); }
    ;

// 됨
Assign_Exp
    : Conditional_Exp                       { $$ = $1; }
    | Unary_Exp Assign_Op Assign_Exp        { $$ = new BExp($2, $1, $3); }

// 됨
Assign_Op   
    : '='                                   { $$ = $1; }
    | ADD_ASSIGN                            { $$ = $1; }
    | SUB_ASSIGN                            { $$ = $1; }
    | MUL_ASSIGN                            { $$ = $1; }
    | DIV_ASSIGN                            { $$ = $1; }
    | MOD_ASSIGN                            { $$ = $1; }
    ;

// 됨
Conditional_Exp    
    : Logical_Or_Exp                                { $$ = $1; } 
    | Logical_Or_Exp '?' Exp ':' Conditional_Exp    
    ;

// 됨
Logical_Or_Exp    
    : Logical_And_Exp                               { $$ = $1; }
    | Logical_Or_Exp OR_OP Logical_And_Exp          { $$ = new BExp("||", $1, $3); }
    ;

// 됨
Logical_And_Exp     
    : Equal_Exp                                     { $$ = $1; }
    | Logical_And_Exp AND_OP Equal_Exp              { $$ = new BExp("&&", $1, $3); }
    ;

// 됨
Equal_Exp          
    : Rational_Exp                                  { $$ = $1; }
    | Equal_Exp EQ_OP Rational_Exp                  { $$ = new BExp("==", $1, $3); }
    | Equal_Exp NE_OP Rational_Exp                  { $$ = new BExp("!=", $1, $3); }
    ;

// 됨
Rational_Exp    
    : Addtive_Exp                                   { $$ = $1; }
    | Rational_Exp '<' Addtive_Exp                  { $$ = new BExp("<", $1, $3); }
    | Rational_Exp '>' Addtive_Exp                  { $$ = new BExp(">", $1, $3); }
    | Rational_Exp LE_OP Addtive_Exp                { $$ = new BExp("<=", $1, $3); }
    | Rational_Exp GE_OP Addtive_Exp                { $$ = new BExp(">=", $1, $3); }
    ;

// 됨
Addtive_Exp     
    : Multiple_Exp                                  { $$ = $1; }
    | Addtive_Exp '+' Multiple_Exp                  { $$ = new BExp("+", $1, $3); }
    | Addtive_Exp '-' Multiple_Exp                  { $$ = new BExp("-", $1, $3); }
    ;

// 됨
Multiple_Exp
    : Unary_Exp                                     { $$ = $1; }
    | Multiple_Exp '*' Unary_Exp                    { $$ = new BExp("*", $1, $3); }    
    | Multiple_Exp '/' Unary_Exp                    { $$ = new BExp("/", $1, $3); }    
    | Multiple_Exp '%' Unary_Exp                    { $$ = new BExp("%", $1, $3); }    
    ;

// 됨
Unary_Exp
    : Postfix_Exp                                   { $$ = $1; }
    | INC_OP Unary_Exp                              { $$ = new UExp("++", $2, TRUE); }
    | DEC_OP Unary_Exp                              { $$ = new UExp("--", $2, TRUE); }
    | Unary_Op Unary_Exp                            { $$ = new UExp($1, $2, TRUE); }
    | SIZEOF Unary_Exp                              { $$ = new UExp("sizeof", $2, TRUE); }
    ;

// 됨
Unary_Op
    : '&'                                           { $$ = $1; }
    | '*'                                           { $$ = $1; }
    | '+'                                           { $$ = $1; }
    | '-'                                           { $$ = $1; }
    | '!'                                           { $$ = $1; }
    ;

// 됨
Postfix_Exp
    : Primary_Exp                                   { $$ = $1; }
    | Postfix_Exp '[' Exp ']'                       { $$ = new UExp("[]", $1, FALSE); }
    | Postfix_Exp PTR_OP IDENTIFIER                 { $$ = new BExp("->", $1, new Id($3)); }
    | Postfix_Exp INC_OP                            { $$ = new UExp("++", $1, FALSE); }
    | Postfix_Exp DEC_OP                            { $$ = new UExp("--", $1, FALSE); }
    ;






// part4. 함수 선언

// 됨 !
Func_Definition
    : FUNC Func_Declarator Compound_Statement
    ;

// 됨 !
Func_Declarator
    : IDENTIFIER '(' Identifier_List ')'
    | IDENTIFIER '(' ')'
    | '(' Identifier_List ')'
    | '(' ')' 
    ;

// 됨 !
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
    : IF '(' Exp ')' Statement %prec IFX
    | IF '(' Exp ')' Statement ELSE Statement
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
