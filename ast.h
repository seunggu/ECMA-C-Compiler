#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <fstream>
#include <vector>

#include "SymbolTable.h"

using namespace std;

#define TRUE 1
#define FALSE 0

class Id;

// Program 클래스
class Decl;

class Program {
public:
    vector<Decl*> decls;

    Program(Decl * decl);
    void printProgram(int lmargin);
    void addDecl(Decl * decl);
    void code(ofstream &outFile, SymbolTable * globalSymbolTable);
    void createSymbolTables(SymbolTable * globalST);
};


// Declaration 클래스 (Abstract Class)
class Decl {
public:
    virtual void printDecl(int lmargin) = 0;
    virtual void code(ofstream &outFile, SymbolTable * symbolTable) = 0;
    virtual int getDeclAmount() = 0;
    virtual void createSymbolTables(SymbolTable * symbolTable) = 0;
    virtual typeKind getType() = 0;
};

// Declaration List 클래스
class DeclList {
public:
    vector<Decl*> decls;

    DeclList(Decl * decl);
    void printDeclList(int lmargin);
    void addDecl(Decl * decl);
    void code(ofstream &outFile, SymbolTable * symbolTable);
    void createSymbolTables(SymbolTable * symbolTable);
};

// VarDecl 클래스
class InitDeclaratorList;

class VarDecl : public Decl {
public:
    InitDeclaratorList * initDecltrList;

    VarDecl();
    VarDecl(InitDeclaratorList * list);
    virtual void printDecl(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
    virtual int getDeclAmount();
    virtual void createSymbolTables(SymbolTable * symbolTable);
    virtual typeKind getType();
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
    void code(ofstream &outFile, SymbolTable * symbolTable);
    void createSymbolTables(SymbolTable * symbolTable);
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
    void code(ofstream &outFile, SymbolTable * symbolTable);
    void createSymbolTables(SymbolTable * symbolTable);
};

// Declarator 클래스
class Declarator {
public:
    virtual void printDeclarator(int lmargin) = 0;
    virtual void code(ofstream &outFile, SymbolTable * symbolTable) = 0;
    virtual Id* getIdentifier() = 0;
};

// Pointer Declarator 클래스
class PointerDeclarator : public Declarator {
public:
    Declarator * declarator;

    PointerDeclarator(Declarator * decl);
    virtual void printDeclarator(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
    virtual Id* getIdentifier();
};

// Identifier Declarator 클래스
class Id;

class IdentifierDeclarator : public Declarator {
public:
    Id * identifier;

    IdentifierDeclarator(Id * id);
    virtual void printDeclarator(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
    virtual Id* getIdentifier();
};









// Exp (추상 클래스)
class Exp {
public:
    virtual void printExp(int lmargin) = 0;
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable) = 0;
};

// Exp List 클래스
class ExpList : public Exp {
public:
    vector<Exp*> expList;

    ExpList(Exp * e);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
    void addExp(Exp * e);
};

// Identifier 클래스
class Id : public Exp {
public:
    string name;

    Id(string n);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
    SymbolEntry* codeL(ofstream &outFile, SymbolTable * symbolTable);
};


// 정수 숫자 리터럴 클래스
class IntNum : public Exp {
public:
    int val;

    IntNum(int val);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};

// 실수 숫자 리터럴 클래스
class DbNum : public Exp {
public:
    double val;

    DbNum(double val);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};

// Boolean 리터럴 클래스
class Bool : public Exp {
public:
    int val;

    Bool(int val);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};

// 문자 리터럴 클래스
class Str : public Exp {
public:
  string str;

    Str(string str);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};

// 리스트 리터럴 클래스
class ECMAList : public Exp {
public:
    vector<Exp*> expList;

    ECMAList();
    ECMAList(Exp * val);
    virtual void printExp(int lmargin);
    void addExp(Exp * val);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};

// 이항 연산자
class BExp : public Exp {
public:
    string op;
    Exp * left;
    Exp * right;

    BExp(string o, Exp * l, Exp * r);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};

// 단항 연산자
class UExp : public Exp {
public:
    int isPre; // PreUnary이면 TRUE, PostUnary이면 FALSE
    string op;
    Exp * exp;

    UExp(string o, Exp * e, int isPre);
    virtual void printExp(int lmargin);
    virtual TypeInfo* codeR(ofstream &outFile, SymbolTable * symbolTable);
};








// Identifier List 클래스
class IdentifierList {
public:
    vector<Id *> identifiers;

    IdentifierList(Id * id);
    void printIdList(int lmargin);
    void addId(Id * id);
    void createSymbolTables(SymbolTable * symbolTable);
    int getAmount();
};

// Function Declarator 클래스
class FuncDeclarator {
public:
    Id * identifier;
    IdentifierList * paramList;

    FuncDeclarator(Id * id, IdentifierList * pl);
    void printDeclarator(int lmargin);
    void code(ofstream &outFile, SymbolTable * symbolTable);
    void createSymbolTables(SymbolTable * symbolTable);
};

// Function Declaration 클래스
class Statement;

class FuncDecl : public Decl {
public:
    FuncDeclarator * funcDeclarator;
    Statement * compoundStatement;

    FuncDecl(FuncDeclarator * funcDecltr, Statement * cpStmt);
    virtual void printDecl(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
    virtual int getDeclAmount();
    virtual void createSymbolTables(SymbolTable * symbolTable);
    virtual typeKind getType();
};




// Statment 클래스 (추상 클래스)
class Statement {
public:
    virtual void printStatement(int lmargin) = 0;
    virtual void code(ofstream &outFile, SymbolTable * symbolTable) = 0;
};

// Statment List 클래스
class StatementList {
public:
    vector<Statement*> statements;

    StatementList(Statement * stmt);
    void printStatementList(int lmargin);
    void addStatement(Statement * stmt);
    void code(ofstream &outFile, SymbolTable * symbolTable);
};

// Compound Statement 클래스
class CompoundStatement : public Statement {
public:
    StatementList * statementList;
    DeclList * declarationList;

    CompoundStatement(StatementList * stmtList, DeclList * declList);

    virtual void printStatement(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
    void createSymbolTable(SymbolTable * symbolTable);
    int getDeclAmount();
};

// Expression Statement 클래스
class ExpStatement : public Statement {
public:
    Exp * exp;

    ExpStatement(Exp * e);
    virtual void printStatement(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
};


// If Statement 클래스
class IfStatement : public Statement {
public:
    Exp * condition;
    Statement * trueStatement;
    Statement * elseStatement;

    IfStatement(Exp * c, Statement * ts, Statement * es);
    virtual void printStatement(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
};

// While Statement 클래스
class WhileStatement : public Statement {
public:
    Exp * condition;
    Statement * statement;

    WhileStatement(Exp * c, Statement * s);
    virtual void printStatement(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
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
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
};

// For In Statement 클래스
class ForInStatement : public Statement {
public:
    Id * initVar;
    Exp * loopExp;
    Statement * statement;

    ForInStatement(Id * i, Exp * le, Statement * stmt);
    virtual void printStatement(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
};

// Jump Statement 클래스
class JumpStatement : public Statement {
public:
    string name;
    Exp * returnExp;

    JumpStatement(string n, Exp * r);
    virtual void printStatement(int lmargin);
    virtual void code(ofstream &outFile, SymbolTable * symbolTable);
};

// traverse 함수
void printTree(Exp * root);

#endif
