%{  // Bison input
    #include <stdio.h>
    #include "ast.h"

    #define TRUE 1
    #define FALSE 0

    int yylex(void);
    int yyerror(char *msg);

    Program * program;
%}

%union {
    const char * sval;
    int ival;
    double dval;
    Exp * expVal;
    Program * prog;
    Declarator * decltr;
    Pointer * ptr;
    Decl * decl;
    DeclList * declList;
    InitDeclarator * initDecltr;
    InitDeclaratorList * initDeclList;
    IdentifierList * idList;
    FuncDeclarator * funcDecltr;
    FuncDecl * funcDecl;
    Statement * stmt;
    StatementList * stmtList;
}



%token SIZEOF FUNC VAR STRUCT IF ELSE WHILE FOR CONTINUE BREAK RETURN
%token INC_OP DEC_OP AND_OP OR_OP EQ_OP NE_OP PTR_OP 
%token <sval> '=' '<' '>'  '&' '*' '+' '-' '!' LE_OP GE_OP 
%token <sval> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN 
%token <sval> IDENTIFIER STRING_LITERAL
%token <ival> INT_LITERAL BOOLEAN_LITERAL
%token <dval> DOUBLE_LITERAL

%type <prog> Program
%type <decltr> Declarator Direct_Declarator
%type <ptr> Pointer
%type <initDecltr> Init_Declarator
%type <initDeclList> Init_Declarator_List
%type <decl> Declaration External_Decl
%type <declList> Declaration_List
%type <idList> Identifier_List
%type <funcDecltr> Func_Declarator
%type <funcDecl> Func_Declaration
%type <stmt> Statement Compound_Statement Exp_Statement Selection_Statement Iteration_Statement Jump_Statement 
%type <stmtList> Statement_List

%type <sval> Assign_Op Unary_Op
%type <expVal> Primary_Exp List_Literal Primary_Exp_List Exp Assign_Exp Conditional_Exp 
%type <expVal> Unary_Exp Logical_Or_Exp Logical_And_Exp Equal_Exp Rational_Exp Addtive_Exp Multiple_Exp Postfix_Exp Func_Identifier


%nonassoc IFX
%nonassoc ELSE

%start Print
%%

// part1: 프로그램 선언

// 됨

Print   
    : Program     { $1 -> printProgram(0); }
    ;

Program
    : External_Decl                                     { $$ = new Program($1); }
    | Program External_Decl                             { $1 -> addDecl($2); $$ = $1; }
    ;

External_Decl
    : Declaration                                       { $$ = $1; }
    | Func_Declaration                                  { $$ = $1; }
    ;







// part2: 변수 선언

Declaration 
    : Declaration_Specifiers ';'                        { $$ = new VarDecl(); }
    | Declaration_Specifiers Init_Declarator_List ';'   { $$ = new VarDecl($2); }
    ;

// 됨 (struct 빠짐)
Declaration_Specifiers
    : VAR
    ;

Init_Declarator_List
    : Init_Declarator                               { $$ = new InitDeclaratorList($1); }
    | Init_Declarator_List ',' Init_Declarator      { $1 -> addInitDeclarator($3); $$ = $1; }
    ;

Init_Declarator
    : Declarator                            { $$ = new InitDeclarator($1); }
    | Declarator '=' Assign_Exp             { $$ = new InitDeclarator($1, $3); }
    ;
 
Declarator
    : Pointer Direct_Declarator             { $$ = new PointerDeclarator($1, $2); }
    | Direct_Declarator                     { $$ = $1; }
    ;

Pointer
    : '*'                                   { $$ = new Pointer(); }
    | '*' Pointer                           { $2 -> addPointerCount(); $$ = $2; }
    ;
 
Direct_Declarator
    : IDENTIFIER                            { $$ = new IdentifierDeclarator(new Id($1)); }
    | '(' Declarator ')'                    { $$ = $2; }
    ;







// part3: 각종 Exp 정리

Primary_Exp
    : IDENTIFIER                            { $$ = new Id($1); }
    | INT_LITERAL                           { $$ = new IntNum($1); }
    | DOUBLE_LITERAL                        { $$ = new DbNum($1); }
    | STRING_LITERAL                        { $$ = new Str($1); }
    | BOOLEAN_LITERAL                       { $$ = new Bool($1); }
    | List_Literal                          { $$ = $1; }
    | '(' Exp ')'                           { $$ = $2; }
    ;

List_Literal
    : '[' Primary_Exp_List ']'              { $$ = $2; }
    | '[' ']'                               { $$ = new ECMAList(); }
    ;

Primary_Exp_List
    : Primary_Exp                           { $$ = new ECMAList($1); }
    | Primary_Exp_List ',' Primary_Exp      { ECMAList * list = (ECMAList *)$1; list -> addExp($3); $$ = $1; }
    ;

Exp
    : Assign_Exp                            { $$ = $1; }
    | Exp ',' Assign_Exp                    { $$ = new BExp(",", $1, $3); }
    ;

Assign_Exp
    : Conditional_Exp                       { $$ = $1; }
    | Unary_Exp Assign_Op Assign_Exp        { $$ = new BExp($2, $1, $3); }

Assign_Op   
    : '='                                   { $$ = "="; }
    | ADD_ASSIGN                            { $$ = "+="; }
    | SUB_ASSIGN                            { $$ = "-="; }
    | MUL_ASSIGN                            { $$ = "*="; }
    | DIV_ASSIGN                            { $$ = "/="; }
    | MOD_ASSIGN                            { $$ = "%="; }
    ;

// 됨
Conditional_Exp    
    : Logical_Or_Exp                                { $$ = $1; } 
    | Logical_Or_Exp '?' Exp ':' Conditional_Exp    
    ;

Logical_Or_Exp    
    : Logical_And_Exp                               { $$ = $1; }
    | Logical_Or_Exp OR_OP Logical_And_Exp          { $$ = new BExp("||", $1, $3); }
    ;

Logical_And_Exp     
    : Equal_Exp                                     { $$ = $1; }
    | Logical_And_Exp AND_OP Equal_Exp              { $$ = new BExp("&&", $1, $3); }
    ;

Equal_Exp          
    : Rational_Exp                                  { $$ = $1; }
    | Equal_Exp EQ_OP Rational_Exp                  { $$ = new BExp("==", $1, $3); }
    | Equal_Exp NE_OP Rational_Exp                  { $$ = new BExp("!=", $1, $3); }
    ;

Rational_Exp    
    : Addtive_Exp                                   { $$ = $1; }
    | Rational_Exp '<' Addtive_Exp                  { $$ = new BExp("<", $1, $3); }
    | Rational_Exp '>' Addtive_Exp                  { $$ = new BExp(">", $1, $3); }
    | Rational_Exp LE_OP Addtive_Exp                { $$ = new BExp("<=", $1, $3); }
    | Rational_Exp GE_OP Addtive_Exp                { $$ = new BExp(">=", $1, $3); }
    ;

Addtive_Exp     
    : Multiple_Exp                                  { $$ = $1; }
    | Addtive_Exp '+' Multiple_Exp                  { $$ = new BExp("+", $1, $3); }
    | Addtive_Exp '-' Multiple_Exp                  { $$ = new BExp("-", $1, $3); }
    ;

Multiple_Exp
    : Unary_Exp                                     { $$ = $1; }
    | Multiple_Exp '*' Unary_Exp                    { $$ = new BExp("*", $1, $3); }    
    | Multiple_Exp '/' Unary_Exp                    { $$ = new BExp("/", $1, $3); }    
    | Multiple_Exp '%' Unary_Exp                    { $$ = new BExp("%", $1, $3); }    
    ;

Unary_Exp
    : Postfix_Exp                                   { $$ = $1; }
    | INC_OP Unary_Exp                              { $$ = new UExp("++", $2, TRUE); }
    | DEC_OP Unary_Exp                              { $$ = new UExp("--", $2, TRUE); }
    | Unary_Op Unary_Exp                            { $$ = new UExp($1, $2, TRUE); }
    | SIZEOF Unary_Exp                              { $$ = new UExp("sizeof", $2, TRUE); }
    ;

Unary_Op
    : '&'                                           { $$ = "&"; }
    | '*'                                           { $$ = "*"; }
    | '+'                                           { $$ = "+"; }
    | '-'                                           { $$ = "-"; }
    | '!'                                           { $$ = "!"; }
    ;

Postfix_Exp
    : Primary_Exp                                   { $$ = $1; }
    | Postfix_Exp '[' Exp ']'                       { $$ = new BExp("[]", $1, $3); }
    | Postfix_Exp PTR_OP IDENTIFIER                 { $$ = new BExp("->", $1, new Id($3)); }
    | Postfix_Exp INC_OP                            { $$ = new UExp("++", $1, FALSE); }
    | Postfix_Exp DEC_OP                            { $$ = new UExp("--", $1, FALSE); }
    ;






// part4. 함수 선언

Func_Declaration
    : FUNC Func_Declarator Compound_Statement       { $$ = new FuncDecl($2, $3); }
    ;

Func_Declarator
    : Func_Identifier '(' Identifier_List ')'            { $$ = new FuncDeclarator((Id*)$1, $3); }
    | Func_Identifier '(' ')'                            { $$ = new FuncDeclarator((Id*)$1, NULL); }
    ;

Func_Identifier
    : IDENTIFIER                                    { $$ = new Id($1); }
    ;

Identifier_List
    : IDENTIFIER                                    { $$ = new IdentifierList(new Id($1)); }
    | Identifier_List ',' IDENTIFIER                { $1 -> addId(new Id($3)); $$ = $1; }
    ;








// part5. Statement 선언

Statement
    : Compound_Statement                            { $$ = $1; }
    | Exp_Statement                                 { $$ = $1; }
    | Selection_Statement                           { $$ = $1; }
    | Iteration_Statement                           { $$ = $1; }
    | Jump_Statement                                { $$ = $1; }                           
    ;

Compound_Statement
    : '{' '}'                                       { $$ = new CompoundStatement(NULL, NULL); }
    | '{' Statement_List '}'                        { $$ = new CompoundStatement($2, NULL); }
    | '{' Declaration_List '}'                      { $$ = new CompoundStatement(NULL, $2); }
    | '{' Declaration_List Statement_List '}'       { $$ = new CompoundStatement($3, $2); }
    ;

Declaration_List 
    : Declaration                                   { $$ = new DeclList($1); }
    | Declaration_List Declaration                  { $1 -> addDecl($2); $$ = $1; }
    ;

Statement_List
    : Statement                                     { $$ = new StatementList($1); }
    | Statement_List Statement                      { $1 -> addStatement($2); $$ = $1; }
    ;

Exp_Statement
    : ';'                                           { $$ = new ExpStatement(NULL); }
    | Exp ';'                                       { $$ = new ExpStatement($1); }
    ;

Selection_Statement
    : IF '(' Exp ')' Statement %prec IFX            { $$ = new IfStatement($3, $5, NULL); }
    | IF '(' Exp ')' Statement ELSE Statement       { $$ = new IfStatement($3, $5, $7); }
    ;

Iteration_Statement
    : WHILE '(' Exp ')' Statement                               { $$ = new WhileStatement($3, $5); }
    | FOR '(' Exp_Statement Exp_Statement ')' Statement         { $$ = new ForStatement($3, $4, NULL, $6); }
    | FOR '(' Exp_Statement Exp_Statement Exp ')' Statement     { $$ = new ForStatement($3, $4, $5, $7); }
    ;

Jump_Statement
    : CONTINUE ';'                                              { $$ = new JumpStatement("continue", NULL); }
    | BREAK ';'                                                 { $$ = new JumpStatement("break", NULL); }
    | RETURN ';'                                                { $$ = new JumpStatement("return", NULL); }
    | RETURN Exp ';'                                            { $$ = new JumpStatement("return", $2); }
    ;



%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
}
