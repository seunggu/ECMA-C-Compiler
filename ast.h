#ifndef __AST_H__
#define __AST_H__

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define TRUE 1
#define FALSE 0

// Program 클래스
class Decl;

class Program {
public:
    vector<Decl*> decls;

    Program(Decl * decl);
    void printProgram(int lmargin);
    void addDecl(Decl * decl);
};


// Declaration 클래스 (Abstract Class)
class Decl {
public:
    virtual void printDecl(int lmargin) = 0;
};

// Declaration List 클래스
class DeclList {
public:
    vector<Decl*> decls;

    DeclList(Decl * decl);
    void printDeclList(int lmargin);
    void addDecl(Decl * decl);
};

// VarDecl 클래스
class InitDeclaratorList;

class VarDecl : public Decl {
public:
    InitDeclaratorList * initDecltrList;

    VarDecl();
    VarDecl(InitDeclaratorList * list);
    virtual void printDecl(int lmargin);
};



// Pointer 클래스
class Pointer {
public:
    int count;

    Pointer();
    void addPointerCount();
    void printPointer(int lmargin);
};

// Init Declarator List 클래스
class InitDeclarator;

class InitDeclaratorList {
public:
    vector<InitDeclarator*> initDeclatrators;

    InitDeclaratorList();
    InitDeclaratorList(InitDeclarator * initDecltr);
    void printInitDeclaratorList(int lmargin);
    void addInitDeclarator(InitDeclarator * initDecltr);
};

// Init Declarator 클래스
class Declarator;
class Exp;

class InitDeclarator {
public:
    Declarator * declarator;
    Exp * exp;

    InitDeclarator(Declarator * decltr);
    InitDeclarator(Declarator * decltr, Exp * e);
    void printInitDeclarator(int lmargin);
};

// Declarator 클래스
class Declarator {
public:
    virtual void printDeclarator(int lmargin) = 0;
};

// Pointer Declarator 클래스
class Pointer;

class PointerDeclarator : public Declarator {
public:
    Pointer * pointer;
    Declarator * declarator;

    PointerDeclarator(Pointer * ptr, Declarator * decl);
    virtual void printDeclarator(int lmargin);
};

// Identifier Declarator 클래스
class Id;

class IdentifierDeclarator : public Declarator {
public:
    Id * identifier;

    IdentifierDeclarator(Id * id);
    virtual void printDeclarator(int lmargin);
};

// Exp (추상 클래스)
class Exp {
public:
    virtual void printExp(int lmargin) = 0;
};

// Identifier 클래스
class Id : public Exp {
public:
    char * name;

    Id(const char * n);
    virtual void printExp(int lmargin);
};


// 정수 숫자 리터럴 클래스
class IntNum : public Exp {
public:
    int val;

    IntNum(int val);
    virtual void printExp(int lmargin);
};

// 실수 숫자 리터럴 클래스
class DbNum : public Exp {
public:
    double val;

    DbNum(double val);
    virtual void printExp(int lmargin);
};

// Boolean 리터럴 클래스
class Bool : public Exp {
public:
    int val;

    Bool(int val);
    virtual void printExp(int lmargin);
};

// 문자 리터럴 클래스
class Str : public Exp {
public:
  char * str;

    Str(const char * str);
    virtual void printExp(int lmargin);
};

// 리스트 리터럴 클래스
class ECMAList : public Exp {
public:
    vector<Exp*> expList;

    ECMAList();
    ECMAList(Exp * val);
    virtual void printExp(int lmargin);
    void addExp(Exp * val);
};

// 이항 연산자
class BExp : public Exp {
public:
    char * op;
    Exp * left;
    Exp * right;

    BExp(const char * o, Exp * l, Exp * r);
    virtual void printExp(int lmargin);
};

// 단항 연산자
class UExp : public Exp {
public:
    int isPre; // PreUnary이면 TRUE, PostUnary이면 FALSE
    char * op;
    Exp * exp;

    UExp(const char * o, Exp * e, int isPre);
    virtual void printExp(int lmargin);
};








// Identifier List 클래스
class IdentifierList {
public:
    vector<Id *> identifiers;

    IdentifierList(Id * id);
    void printIdList(int lmargin);
    void addId(Id * id);
};

// Function Declarator 클래스
class FuncDeclarator {
public:
    Id * identifier;
    IdentifierList * paramList;

    FuncDeclarator(Id * id, IdentifierList * pl);
    void printDeclarator(int lmargin);
};

// Function Declaration 클래스
class Statement;

class FuncDecl : public Decl {
public:
    FuncDeclarator * funcDeclarator;
    Statement * compoundStatement;

    FuncDecl(FuncDeclarator * funcDecltr, Statement * cpStmt);;
    virtual void printDecl(int lmargin);
};




// Statment 클래스 (추상 클래스)
class Statement {
public:
    virtual void printStatement(int lmargin) = 0;
};

// Statment List 클래스
class StatementList {
public:
    vector<Statement*> statements;

    StatementList(Statement * stmt);
    void printStatementList(int lmargin);
    void addStatement(Statement * stmt);
};

// Compound Statement 클래스
class CompoundStatement : public Statement {
public:
    StatementList * statementList;
    DeclList * declarationList;

    CompoundStatement(StatementList * stmtList, DeclList * declList);
    virtual void printStatement(int lmargin);
};

// Expression Statement 클래스
class ExpStatement : public Statement {
public:
    Exp * exp;

    ExpStatement(Exp * e);
    virtual void printStatement(int lmargin);
};


// If Statement 클래스
class IfStatement : public Statement {
public:
    Exp * condition;
    Statement * trueStatement;
    Statement * elseStatement;

    IfStatement(Exp * c, Statement * ts, Statement * es);
    virtual void printStatement(int lmargin);
};

// While Statement 클래스
class WhileStatement : public Statement {
public:
    Exp * condition;
    Statement * statement;

    WhileStatement(Exp * c, Statement * s);
    virtual void printStatement(int lmargin);
};

// For Statement 클래스
class ForStatement : public Statement {
public:
    Statement * initStatement;
    Statement * conditionStatement;
    Exp * lastExp;
    Statement * statement;

    ForStatement(Statement * i, Statement * c, Exp * l, Statement * s);
    virtual void printStatement(int lmargin);
};

// For In Statement 클래스
class ForInStatement : public Statement {
public:
    Id * initVar;
    Exp * loopExp;
    Statement * statement;

    ForInStatement(Id * i, Exp * le, Statement * stmt);
    virtual void printStatement(int lmargin);
};

// Jump Statement 클래스
class JumpStatement : public Statement {
public:
    char * name;
    Exp * returnExp;

    JumpStatement(const char * n, Exp * r);
    virtual void printStatement(int lmargin);
};

// traverse 함수
void printTree(Exp * root);

#endif
