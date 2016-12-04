#include "ast.h"

#include <cstdlib>
#include <cstring>

const int INDENT_LEVEL = 4;
void indent(int n);

// Exp 리스트 클래스
ExpList::ExpList(char * l) {

}


// Exp 클래스
void Exp::print(int lmargin) {
    printExp(lmargin);
}

// ID 리터럴 클래스
Id::Id(const char * n) {
    name = (char*)malloc(strlen(n));
    strcpy(name, n);
}

void Id::printExp(int lmargin) {
    indent(lmargin);
    printf("Id(%s) \n", name);
}

// 정수 숫자 리터럴 클래스
IntNum::IntNum(int val) : val(val) { }

void IntNum::printExp(int lmargin) {
    indent(lmargin);
    printf("Int(%d) \n", val);
}

// 실수 숫자 리터럴 클래스
DbNum::DbNum(double val) : val(val) { }

void DbNum::printExp(int lmargin) {
    indent(lmargin);
    printf("Int(%lf) \n", val);
}

// 정수 숫자 리터럴 클래스
Bool::Bool(int val) : val(val) { }

void Bool::printExp(int lmargin) {
    indent(lmargin);
    printf("Bool(%s) \n", val == TRUE ? "TRUE" : "FALSE");
}

// 문자 리터럴 클래스
Str::Str(const char * s) {
    str = (char*)malloc(strlen(s));
    strcpy(str, s);
}

void Str::printExp(int lmargin) {
    indent(lmargin);
    printf("Str(\"%s\") \n", str);
}


// 이항 연산자 클래스
BExp::BExp(const char * o, Exp *l, Exp *r) : left(l), right(r) {
    op = (char*)malloc(strlen(o));
    strcpy(op, o);
}

void BExp::printExp(int lmargin) {
    indent(lmargin);
    printf("Op(%s) \n", op);
    left -> printExp(lmargin + INDENT_LEVEL);
    right -> printExp(lmargin + INDENT_LEVEL);
}

// 단항 연산자 클래스
UExp::UExp(const char * o, Exp * e, int isPre) : exp(e), isPre(isPre){
    op = (char*)malloc(strlen(o));
    strcpy(op, o);
}

void UExp::printExp(int lmargin) {
    indent(lmargin);
    printf("Uop(%s) \n", op);
    exp -> printExp(lmargin + INDENT_LEVEL);
}


// 헬퍼 메서드
void printTree(Exp * root)
{
    if (root == NULL) return;
    root -> print(0);
}

void indent(int n)
{
    if (n > 0) {
        printf(" ");
        indent(--n);
    }
}
