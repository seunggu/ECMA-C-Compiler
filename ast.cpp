#include "ast.h"

#include <cstdlib>
#include <cstring>

const int INDENT_LEVEL = 4;
void indent(int n);

// Program 클래스
Program::Program(Decl * decl) {
    decls.push_back(decl);
}

void Program::printProgram(int lmargin) {
    int declCount = (int)decls.size();

    indent(lmargin);
    cout << "Program" << endl;

    if (declCount > 0) {
        for (int i = 0; i < declCount; i++) {
            decls[i] -> printDecl(lmargin + INDENT_LEVEL);
        }
    }
}

void Program::addDecl(Decl * decl) {
    decls.push_back(decl);
}

// VarDecl 클래스
VarDecl::VarDecl() : initDecltrList(NULL) { }

VarDecl::VarDecl(InitDeclaratorList * list) : initDecltrList(list) { }

void VarDecl::printDecl(int lmargin) {
    cout << "Variable Declaration" << endl;

    if (initDecltrList != NULL) {
        initDecltrList -> printInitDeclaratorList(lmargin + INDENT_LEVEL);
    }
}








// Pointer 클래스
Pointer::Pointer() : count(1) { }

void Pointer::addPointerCount() {
    count++;
}

void Pointer::printPointer(int lmargin) {
    indent(lmargin);

    for (int i = 0; i < count; i++) {
        cout << "*";
        cout << endl;
    }
}

// Init Declarator List 클래스
InitDeclaratorList::InitDeclaratorList() { }

InitDeclaratorList::InitDeclaratorList(InitDeclarator * initDecltr) {
    initDeclatrators.push_back(initDecltr);
}

void InitDeclaratorList::printInitDeclaratorList(int lmargin) {
    int initDecltrCount = (int)initDeclatrators.size();

    indent(lmargin);
    cout << "Init Declarator List" << endl;

    if (initDecltrCount > 0) {
        for (int i = 0; i < initDecltrCount; i++) {
            initDeclatrators[i] -> printInitDeclarator(lmargin + INDENT_LEVEL);
        }
    }
}

void InitDeclaratorList::addInitDeclarator(InitDeclarator * initDecltr) {
    initDeclatrators.push_back(initDecltr);
}

// Init Declarator 클래스
InitDeclarator::InitDeclarator(Declarator * decltr) : declarator(decltr) {
    exp = NULL;
}

InitDeclarator::InitDeclarator(Declarator * decltr, Exp * e) : declarator(decltr), exp(e) { }

void InitDeclarator::printInitDeclarator(int lmargin) {
    indent(lmargin);
    cout << "Init Declarator" << endl;

    declarator -> printDeclarator(lmargin + INDENT_LEVEL);
    exp -> printExp(lmargin + INDENT_LEVEL);
}

// Pointer Declarator 클래스
PointerDeclarator::PointerDeclarator(Pointer * ptr, Declarator * decl) : pointer(ptr), declarator(decl) { }

void PointerDeclarator::printDeclarator(int lmargin) {
    indent(lmargin);
    cout << "Pointer Declarator" << endl;

    pointer -> printPointer(lmargin + INDENT_LEVEL);
    declarator -> printDeclarator(lmargin + INDENT_LEVEL);
}

// Identifier Declarator 클래스
IdentifierDeclarator::IdentifierDeclarator(Id * id) : identifier(id) { }

void IdentifierDeclarator::printDeclarator(int lmargin) {
    indent(lmargin);
    cout << "Identifier Declarator" << endl;

    identifier -> printExp(lmargin + INDENT_LEVEL);
}


// Identifier 클래스
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

// 불리언 리터럴 클래스
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
    printf("String(%s) \n", str);
}

// 리스트 리터럴 클래스
ECMAList::ECMAList() { }

ECMAList::ECMAList(Exp * val) {
    expList.push_back(val);
}

void ECMAList::printExp(int lmargin) {
    int expCount = (int)expList.size();

    indent(lmargin);
    printf("List \n");

    if (expCount > 0) {
        for (int i = 0; i < expCount; i++) {
            expList[i] -> printExp(lmargin + INDENT_LEVEL);
        }
    }
}

void ECMAList::addExp(Exp * val) {
    expList.push_back(val);
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


void indent(int n)
{
    if (n > 0) {
        printf(" ");
        indent(--n);
    }
}
