#ifndef __AST_H__
#define __AST_H__

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define TRUE 1
#define FALSE 0

// Program 클래스
class Program {
public:
    TransUnit * transUnit;

    Program(TransUnit * unit);
    void printProgram(int lmargin);
};

// TransUnit 클래스
class TransUnit {
public:
    vector<Decl*> decls;

    TransUnit();
    void printTransUnit(int lmargin);
};

// Decl (Abstract Class)
class Decl {
public:
    virtual void printDecl(int lmargin) = 0;
};

// VarDecl 클래스
class VarDecl : public Decl {
    DecltrInitList * decltrInitList;

    VarDecl();
    VarDecl(DecltrInitList * list);
    virtual void printDecl(int lmargin);
};

// DecltrInitList 클래스
class DecltrInitList {
    vector<DecltrInit*> decltrInits;

    void pushBack(DecltrInit * init);
    void printDecltrInitList(int lmargin);
};

class DecltrInit {

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
    Exp * val;

    ECMAList();
    ECMAList(Exp * val);
    virtual void printExp(int lmargin);
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

// 함수 Idenfier와 Parameter 클래스
class FuncIdParam : public Exp {
public:
    Exp * idenifier;
    Exp * parameterList;

    FuncIdParam(Exp * id, Exp * param);
    virtual void printExp(int lmargin);
};

// 함수 클래스
class Func : public Exp {
public:
    Exp * funcIdParam;
    Exp * statement;

    Func(Exp * idParam, Exp * stmt);
    virtual void printExp(int lmargin);
};

// If Statement 클래스
class IfStatement : public Exp {
public:
    Exp * condition;
    Exp * statement;
    Exp * elseStatement;

    IfStatement(Exp * c, Exp * s, Exp * e);
    virtual void printExp(int lmargin);
};

// While Statement 클래스
class WhileStatement : public Exp {
public:
    Exp * condition;
    Exp * statement;

    WhileStatement(Exp * c, Exp * s);
    virtual void printExp(int lmargin);
};

// For Statement 클래스
class ForStatement : public Exp {
public:
    Exp * initStatement;
    Exp * conditionStatement;
    Exp * lastExp;
    Exp * statement;

    ForStatement(Exp * i, Exp * c, Exp * l, Exp * s);
    virtual void printExp(int lmargin);
};

// Compound Statement 클래스
class CompoundStatement : public Exp {
public:
    Exp * statement;
    Exp * declaration;

    CompoundStatement(Exp * stmt, Exp * decl);
    virtual void printExp(int lmargin);
};

// Jump Statement 클래스
class JumpStatement : public Exp {
public:
    char * name;
    Exp * returnExp;

    JumpStatement(const char * n, Exp * r);
    virtual void printExp(int lmargin);
};

// traverse 함수
void printTree(Exp * root);

#endif
