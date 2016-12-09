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
    indent(lmargin);
    cout << "Variable Declaration" << endl;

    if (initDecltrList != NULL) {
        initDecltrList -> printInitDeclaratorList(lmargin + INDENT_LEVEL);
    }
}

// Declaration List 클래스
DeclList::DeclList(Decl * decl) {
    decls.push_back(decl);
}

void DeclList::printDeclList(int lmargin) {
    int declCount = (int)decls.size();

    indent(lmargin);
    cout << "Declation List" << endl;

    if (declCount > 0) {
        for (int i = 0; i < declCount; i++) {
            decls[i] -> printDecl(lmargin + INDENT_LEVEL);
        }
    }
}

void DeclList::addDecl(Decl *decl) {
    decls.push_back(decl);
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








// Identifier List 클래스
IdentifierList::IdentifierList(Id * id) {
    identifiers.push_back(id);
}

void IdentifierList::printIdList(int lmargin) {
    int idCount = (int)identifiers.size();

    indent(lmargin);
    cout << "Id List" << endl;

    if (idCount > 0) {
        for (int i = 0; i < idCount; i++) {
            identifiers[i] -> printExp(lmargin + INDENT_LEVEL);
        }
    }
}

void IdentifierList::addId(Id * id) {
    identifiers.push_back(id);
}

// Function Declarator 클래스
FuncDeclarator::FuncDeclarator(Id * id, IdentifierList * pl) : identifier(id) {
    if (pl == NULL) {
        paramList = NULL;
    } else {
        paramList = pl;
    }
}

void FuncDeclarator::printDeclarator(int lmargin) {
    indent(lmargin);
    cout << "Function Declarator" << endl;

    identifier -> printExp(lmargin + INDENT_LEVEL);

    if (paramList != NULL) {
        paramList -> printIdList(lmargin + INDENT_LEVEL);
    }
}

// Function Declaration 클래스
FuncDecl::FuncDecl(FuncDeclarator * funcDecltr, Statement * cpStmt)
        : funcDeclarator(funcDecltr), compoundStatement(cpStmt) { }

void FuncDecl::printDecl(int lmargin) {
    indent(lmargin);
    cout << "Function Declaration" << endl;

    funcDeclarator -> printDeclarator(lmargin + INDENT_LEVEL);
    compoundStatement -> printStatement(lmargin + INDENT_LEVEL);;
}











// Statement List 클래스
StatementList::StatementList(Statement * stmt) {
    statements.push_back(stmt);
}

void StatementList::printStatementList(int lmargin) {
    int stmtCount = (int)statements.size();

    indent(lmargin);
    cout << "Statement List" << endl;

    if (stmtCount > 0) {
        for (int i = 0; i < stmtCount; i++) {
            statements[i] -> printStatement(lmargin + INDENT_LEVEL);
        }
    }
}

void StatementList::addStatement(Statement * stmt) {
    statements.push_back(stmt);
}

// Compound Statement 클래스
CompoundStatement::CompoundStatement(StatementList * stmtList, DeclList * declList) {
    if (stmtList == NULL && declList == NULL) {
        statementList = NULL;
        declarationList = NULL;
    } else if (stmtList == NULL) {
        statementList = NULL;
        declarationList = declList;
    } else if (declList == NULL) {
        statementList = stmtList;
        declarationList = NULL;
    } else {
        statementList = stmtList;
        declarationList = declList;
    }
}

void CompoundStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "Compound Statement" << endl;

    if (declarationList != NULL) {
        declarationList -> printDeclList(lmargin + INDENT_LEVEL);
    }

    if (statementList != NULL) {
        statementList -> printStatementList(lmargin + INDENT_LEVEL);
    }
}

// Expression Statement 클래스
ExpStatement::ExpStatement(Exp * e) {
    if (e == NULL) {
        exp = NULL;
    } else {
        exp = e;
    }
}

void ExpStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "Exp Statement" << endl;

    if (exp != NULL) {
        exp -> printExp(lmargin + INDENT_LEVEL);
    }
}


// If Statement 클래스
IfStatement::IfStatement(Exp * c, Statement * ts, Statement * es) : condition(c), trueStatement(ts) {
    if (es == NULL) {
        elseStatement = NULL;
    } else {
        elseStatement = es;
    }
}

void IfStatement::printStatement(int lmargin) {
    indent(lmargin);

    if (elseStatement != NULL) {
        cout << "If ELSE Statement" << endl;
    } else {
        cout << "If Statement" << endl;
    }

    condition -> printExp(lmargin + INDENT_LEVEL);
    trueStatement -> printStatement(lmargin + INDENT_LEVEL);

    if (elseStatement != NULL) {
        elseStatement -> printStatement(lmargin + INDENT_LEVEL);
    }
}

// While Statement 클래스
WhileStatement::WhileStatement(Exp * c, Statement * s) : condition(c), statement(s) { }

void WhileStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "While Statement" << endl;
    condition -> printExp(lmargin + INDENT_LEVEL);
    statement -> printStatement(lmargin + INDENT_LEVEL);
}

// For Statement 클래스
ForStatement::ForStatement(Statement * i, Statement * c, Exp * l, Statement * s)
        : initStatement(i), conditionStatement(c), statement(s) {
    if (l == NULL) {
        lastExp = NULL;
    } else {
        lastExp = l;
    }
}

void ForStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "For Statement" << endl;
    initStatement -> printStatement(lmargin + INDENT_LEVEL);
    conditionStatement -> printStatement(lmargin + INDENT_LEVEL);
    statement -> printStatement(lmargin + INDENT_LEVEL);

    if (lastExp != NULL) {
        lastExp -> printExp(lmargin + INDENT_LEVEL);
    }
}

// For In Statement 클래스
ForInStatement::ForInStatement(Id * i, Exp * le, Statement * stmt)
        : initVar(i), loopExp(le), statement(stmt) { }

void ForInStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "For In Statement" << endl;

    initVar -> printExp(lmargin + INDENT_LEVEL);
    loopExp -> printExp(lmargin + INDENT_LEVEL);
    statement -> printStatement(lmargin + INDENT_LEVEL);
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

void JumpStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "JumpStatement(" << name << ")" << endl;

    if ((strcmp(name, "return") == 0) && returnExp != NULL) {
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
