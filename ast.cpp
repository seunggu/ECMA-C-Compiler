#include "ast.h"

#include <cstdlib>
#include <cstring>

const int INDENT_LEVEL = 4;
void indent(int n);


// Program 클래스
Program::Program(TransUnit * unit) : transUnit(unit) { }

void Program::printProgram(int lmargin) {
    cout << "Program" << endl;
    transUnit -> printTransUnit(lmargin + INDENT_LEVEL);
}

// TransUnit 클래스
TransUnit::TransUnit() { }

void TransUnit::printTransUnit(int lmargin) {
    int countOfDecls = (int)decls.size();
    cout << "Decls" << endl;

    for (int i = 0; i < countOfDecls; i++) {
        decls[i] -> printDecl(lmargin + INDENT_LEVEL);
    }
}

// VarDecl 클래스
VarDecl::VarDecl() : decltrInitList(NULL) { }

VarDecl::VarDecl(DecltrInitList *list) : decltrInitList(list) { }

void VarDecl::printDecl(int lmargin) {
    cout << "VarDecl" << endl;

    if (decltrInitList != NULL) {
        //decltrInitList
    }
}

// DecltrInitList 클래스
void DecltrInitList::pushBack(DecltrInit * init) {
    decltrInits.push_back(init);
}

void DecltrInitList::printDecltrInitList(int lmargin) {
    int countOfDecls = (int)decltrInits.size();
    cout << "Declator Init List" << endl;

    for (int i = 0; i < countOfDecls; i++) {
        //decltrInits[i] -> printDecl(lmargin + INDENT_LEVEL);
    }
}


// Exp 클래스
void Exp::print(int lmargin) {
    printExp(lmargin);
}

void Exp::printExp(int lmargin) {

}

// Multi Exp 클래스
MultiExp::MultiExp(Exp *l, Exp *r) : left(l), right(r) { }

void MultiExp::printExp(int lmargin) {
    indent(lmargin);
    left -> printExp(lmargin);
    right -> printExp(lmargin);
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
    printf("Double(%lf) \n", val);
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
    printf("Str(%s) \n", str);
}

// 리스트 리터럴 클래스
ECMAList::ECMAList() : val(NULL) { }
ECMAList::ECMAList(Exp * val) : val(val) { }

void ECMAList::printExp(int lmargin) {
    indent(lmargin);
    printf("List() \n");
    val -> printExp(lmargin + INDENT_LEVEL);
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

// 함수 Idenfier와 Parameter 클래스
FuncIdParam::FuncIdParam(Exp * id, Exp * param) {
    if (id == NULL && param == NULL) {
        idenifier = NULL;
        parameterList = NULL;
    } else if (id == NULL) {
        idenifier = NULL;
        parameterList = param;
    } else if (param == NULL) {
        idenifier = id;
        parameterList = NULL;
    } else {
        idenifier = id;
        parameterList = param;
    }
}

void FuncIdParam::printExp(int lmargin) {
    indent(lmargin);

    if (idenifier == NULL && parameterList == NULL) {
        printf("Func No Identifier And No Parameter Info \n");
    } else if (idenifier == NULL) {
        printf("Func Parameter Info \n");
        parameterList -> printExp(lmargin + INDENT_LEVEL);
    } else if (parameterList == NULL) {
        printf("Func Identifier Info \n");
        idenifier -> printExp(lmargin + INDENT_LEVEL);;
    } else {
        printf("Func Identifier And Parameter Info \n");
        idenifier -> printExp(lmargin + INDENT_LEVEL);
        parameterList -> printExp(lmargin + INDENT_LEVEL);
    };
}


// 함수 클래스
Func::Func(Exp * idParam, Exp * stmt) : funcIdParam(idParam), statement(stmt) { }

void Func::printExp(int lmargin) {
    indent(lmargin);
    printf("func \n");
    funcIdParam -> printExp(lmargin + INDENT_LEVEL);
    statement -> printExp(lmargin + INDENT_LEVEL);
}

// If Statement
IfStatement::IfStatement(Exp * c, Exp * s, Exp * e) : condition(c), statement(s) {
    if (e == NULL) {
        elseStatement = NULL;
    } else {
        elseStatement = e;
    }
}

void IfStatement::printExp(int lmargin) {
    indent(lmargin);

    if (elseStatement != NULL) {
        printf("If ELSE");
    } else {
        printf("If");
    }

    condition -> printExp(lmargin + INDENT_LEVEL);
    statement -> printExp(lmargin + INDENT_LEVEL);

    if (elseStatement != NULL) {
        elseStatement -> printExp(lmargin + INDENT_LEVEL);
    }
}

// While Statement 클래스
WhileStatement::WhileStatement(Exp * c, Exp * s) : condition(c), statement(s) { }

void WhileStatement::printExp(int lmargin) {
    indent(lmargin);
    printf("While");
    condition -> printExp(lmargin + INDENT_LEVEL);
    statement -> printExp(lmargin + INDENT_LEVEL);
}

// For Statement 클래스
ForStatement::ForStatement(Exp *i, Exp *c, Exp *l, Exp *s) : initStatement(i), conditionStatement(c), statement(s) {
    if (l == NULL) {
        lastExp = NULL;
    } else {
        lastExp = l;
    }
}

void ForStatement::printExp(int lmargin) {
    indent(lmargin);
    printf("For");
    initStatement -> printExp(lmargin + INDENT_LEVEL);
    conditionStatement -> printExp(lmargin + INDENT_LEVEL);
    if (lastExp != NULL) {
        lastExp -> printExp(lmargin + INDENT_LEVEL);
    }
    statement -> printExp(lmargin + INDENT_LEVEL);
}

// Compound Statement 클래스
CompoundStatement::CompoundStatement(Exp * stmt, Exp * decl) {
    if (stmt == NULL && decl == NULL) {
        statement = NULL;
        declaration = NULL;
    } else if (stmt == NULL) {
        statement = NULL;
        declaration = decl;
    } else if (decl == NULL) {
        statement = stmt;
        declaration = NULL;
    } else {
        statement = stmt;
        declaration = decl;
    }
}

void CompoundStatement::printExp(int lmargin) {
    indent(lmargin);
    printf("Compound Statement \n");
    statement -> printExp(lmargin + INDENT_LEVEL);
    declaration -> printExp(lmargin + INDENT_LEVEL);
}

// Jump Statement 클래스
JumpStatement::JumpStatement(const char * n, Exp * r) {
    name = (char*)malloc(strlen(n));
    strcpy(name, n);

    if (r == NULL) {
        returnExp = NULL;
    } else {
        returnExp = r;
    }
}

void JumpStatement::printExp(int lmargin) {
    indent(lmargin);
    printf("JumpStatement(%s) \n", name);

    if (strcmp(name, "return") && returnExp != NULL) {
        returnExp -> printExp(lmargin + INDENT_LEVEL);
    }
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
