#ifndef __AST_H__
#define __AST_H__

#include <cstdio>

using namespace std;

#define TRUE 1
#define FALSE 0

// 프로그램 클래스
class Program {
public:
    virtual void print(int lmargin) = 0;
};



// Exp 추상 클래스
class Exp {
public:
    virtual void print(int lmargin);
    virtual void printExp(int lmargin);
};

class MultiExp : public Exp {
public:
    Exp * left;
    Exp * right;

    MultiExp(Exp * l, Exp * r);
    virtual void printExp(int lmargin);
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

class UExp : public Exp {
public:
    int isPre; // PreUnary이면 TRUE, PostUnary이면 FALSE
    char * op;
    Exp * exp;

    UExp(const char * o, Exp * e, int isPre);
    virtual void printExp(int lmargin);
};

// traverse 함수
void printTree(Exp * root);

#endif
