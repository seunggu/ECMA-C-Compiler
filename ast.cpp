#include "ast.h"

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

void Program::code(ofstream &outFile, SymbolTable * globalSymbolTable) {
    int declCount = (int)decls.size();

    if (declCount > 0) {
        // ssp할 변수 선언 갯수 알아내기
        int total = 0;

        for (int i = 0; i < declCount; i++) {
            total += decls[i] -> getDeclAmount();
        }

        outFile << "\tssp " + to_string(total) << endl;

        // 변수 먼저 선언 후 함수 선언

        for (int i = 0; i < declCount; i++) {
            if (decls[i] -> getType() == ID) {
                decls[i] -> code(outFile, globalSymbolTable);
            }
        }

        if (globalSymbolTable -> getEntry("main") != NULL) {
            outFile << "\tmst" << endl;
            outFile << "\tcup 0 main" << endl;
        }

        for (int i = 0; i < declCount; i++) {
            if (decls[i] -> getType() == FUNCTION) {
                decls[i] -> code(outFile, globalSymbolTable);
            }
        }
    }
}

void Program::createSymbolTables(SymbolTable *globalST) {
    int declCount = (int)decls.size();

    if (declCount > 0) {
        for (int i = 0; i < declCount; i++) {
            decls[i] -> createSymbolTables(globalST);
        }
    }
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

void VarDecl::code(ofstream &outFile, SymbolTable * symbolTable) {
    initDecltrList -> code(outFile, symbolTable);
}

int VarDecl::getDeclAmount() {
    return (int)initDecltrList -> initDeclatrators.size();
}

void VarDecl::createSymbolTables(SymbolTable *symbolTable) {
    initDecltrList -> createSymbolTables(symbolTable);
}

typeKind VarDecl::getType() {
    return ID;
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

void DeclList::code(ofstream &outFile, SymbolTable *symbolTable) {
    int declCount = (int)decls.size();

    if (declCount > 0) {

        // 변수 먼저 선언 후 함수 선언
        for (int i = 0; i < declCount; i++) {
            if (decls[i] -> getType() == ID) {
                decls[i] -> code(outFile, symbolTable);
            }
        }

        for (int i = 0; i < declCount; i++) {
            if (decls[i] -> getType() == FUNCTION) {
                decls[i] -> code(outFile, symbolTable);
            }
        }
    }
}

void DeclList::createSymbolTables(SymbolTable *symbolTable) {
    int declCount = (int)decls.size();

    if (declCount > 0) {
        for (int i = 0; i < declCount; i++) {
            decls[i] -> createSymbolTables(symbolTable);
        }
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

void InitDeclaratorList::code(ofstream &outFile, SymbolTable *symbolTable) {
    int initDecltrCount = (int)initDeclatrators.size();

    if (initDecltrCount > 0) {
        for (int i = 0; i < initDecltrCount; i++) {
            initDeclatrators[i] -> code(outFile, symbolTable);
        }
    }
}

void InitDeclaratorList::createSymbolTables(SymbolTable *symbolTable) {
    int initDecltrCount = (int)initDeclatrators.size();

    if (initDecltrCount > 0) {
        for (int i = 0; i < initDecltrCount; i++) {
            initDeclatrators[i] -> createSymbolTables(symbolTable);
        }
    }
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

    if (exp != NULL) {
        exp -> printExp(lmargin + INDENT_LEVEL);
    }
}

void InitDeclarator::code(ofstream &outFile, SymbolTable *symbolTable) {
    declarator -> code(outFile, symbolTable);

    if (exp != NULL) {
        Id * iden = declarator -> getIdentifier();
        TypeInfo * type = exp -> codeR(outFile, symbolTable);
        outFile << "\tsto" << endl;
        // 심볼 테이블의 변수 타입 변경
        symbolTable -> changeType(iden -> name, type);
    }
}

void InitDeclarator::createSymbolTables(SymbolTable *symbolTable) {
    symbolTable -> setSymbolTableEntry(declarator -> getIdentifier() -> name, NONE);
}

// Pointer Declarator 클래스
PointerDeclarator::PointerDeclarator(Declarator * decl) : declarator(decl) { }

void PointerDeclarator::printDeclarator(int lmargin) {
    indent(lmargin);
    cout << "Pointer Declarator" << endl;

    cout << "Pointer(*)" << endl;
    declarator -> printDeclarator(lmargin + INDENT_LEVEL);
}

void PointerDeclarator::code(ofstream &outFile, SymbolTable *symbolTable) {
    declarator -> code(outFile, symbolTable);
}

Id* PointerDeclarator::getIdentifier() {
    return declarator -> getIdentifier();
}

// Identifier Declarator 클래스
IdentifierDeclarator::IdentifierDeclarator(Id * id) : identifier(id) { }

void IdentifierDeclarator::printDeclarator(int lmargin) {
    indent(lmargin);
    cout << "Identifier Declarator" << endl;

    identifier -> printExp(lmargin + INDENT_LEVEL);
}

void IdentifierDeclarator::code(ofstream &outFile, SymbolTable * symbolTable) {
    identifier -> codeL(outFile, symbolTable);
}

Id* IdentifierDeclarator::getIdentifier() {
    return identifier;
}





// Exp List 클래스
ExpList::ExpList(Exp *e) {
    expList.push_back(e);
}

void ExpList::addExp(Exp *e) {
    expList.push_back(e);
}

void ExpList::printExp(int lmargin) {
    int expCount = (int)expList.size();

    if (expCount > 0) {
        for (int i = 0; i < expCount; i++) {
            expList[i] -> printExp(lmargin + INDENT_LEVEL);
        }
    }
}

TypeInfo* ExpList::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    int expCount = (int)expList.size();
    TypeInfo * typeInfo;

    if (expCount > 0) {
        for (int i = 0; i < expCount; i++) {
            typeInfo = expList[i] -> codeR(outFile, symbolTable);
        }
    }

    return typeInfo;
}


// Identifier 클래스
Id::Id(string n) : name(n) { }

void Id::printExp(int lmargin) {
    indent(lmargin);
    cout << "Id(" + name + ")" << endl;
}

TypeInfo* Id::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    SymbolEntry * entry = codeL(outFile, symbolTable);
    outFile << "\tind" << endl;

    if (entry -> type == INT) {
        return new IDType(new IntType());
    } else if (entry -> type == DOUBLE) {
        return new IDType(new DoubleType());
    } else if (entry -> type == BOOL) {
        return new IDType(new BoolType());
    } else if (entry -> type == STRING) {
        int length = ((StringSymbolEntry*)entry) -> vectorLength;
        return new IDType(new StringType(length));
    } else if (entry -> type == LIST) {
        int length = ((ListSymbolEntry*)entry) -> vectorLength;
        TypeInfo * typeInfo = ((ListSymbolEntry*)entry) -> typeInfo;
        return new IDType(new ListType(length, typeInfo));
    } else {
        return new IDType(new NoneType());
    }
}

SymbolEntry* Id::codeL(ofstream &outFile, SymbolTable *symbolTable) {
    SymbolEntry * entry = symbolTable -> getEntry(name);
    int level = entry -> level;
    int offset = entry -> offset;

    if (symbolTable -> level == level) {
        // 같은 스코프
        outFile << "\tlda " + to_string(offset) << endl;
    } else {
        // 전역 스포프 지원하나 다른 스코프 지원 x
        if (level == 0) {
            outFile << "\tldc " + to_string(offset) << endl;
        } else {
            int levelDiff = (symbolTable -> level) - level;
            for (int i = 0; i < levelDiff; i++) {
                if (i == 0) {
                    outFile << "\tlda 1" << endl;
                } else {
                    outFile << "\tldc 1" << endl;
                    outFile << "\tadd" << endl;
                };

                outFile << "\tind" << endl;
            }
            outFile << "\tldc " + to_string(offset) << endl;
            outFile << "\tadd" << endl;
        }
    }

    return entry;
}

// 정수 숫자 리터럴 클래스
IntNum::IntNum(int val) : val(val) { }

void IntNum::printExp(int lmargin) {
    indent(lmargin);
    cout << "Int(" + to_string(val) + ")" << endl;
}

TypeInfo* IntNum::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    outFile << "\tldc " + to_string(val) << endl;
    return new IntType();
}

// 실수 숫자 리터럴 클래스
DbNum::DbNum(double val) : val(val) { }

void DbNum::printExp(int lmargin) {
    indent(lmargin);
    cout << "Double(" + to_string(val) + ")" << endl;
}

TypeInfo* DbNum::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    cout << "DOUBLE isn`t support yet" << endl;
    exit(1);
}

// 불리언 리터럴 클래스
Bool::Bool(int val) : val(val) { }

void Bool::printExp(int lmargin) {
    indent(lmargin);
    cout << "Bool(" + to_string(val) + ")" << endl;
}

TypeInfo* Bool::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    outFile << "\tldc " + to_string(val) << endl;
    return new BoolType();
}

// 문자 리터럴 클래스
Str::Str(string s) : str(s) { }

void Str::printExp(int lmargin) {
    indent(lmargin);
    cout << "String(" + str + ")" << endl;
}

TypeInfo* Str::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    string pushStr = (((Str*)left) -> str);
    int strSize = (int)pushStr.size();

    outFile << "\tnew " + to_string(strSize + 1) << endl;

    for (int i = 0; i < strSize; i++) {
        string ldc = "\tldc '";
        string sti = "\tsti ";
        outFile << ldc + pushStr[i] + "'" << endl;
        outFile << sti + to_string(i) << endl;
    }
    string sti = "\tsti ";
    outFile << "\tldc '\n'" << endl;
    outFile << sti + to_string(strSize - 1) << endl;
    return new StringType(strSize);
}

// 리스트 리터럴 클래스
ECMAList::ECMAList() { }

ECMAList::ECMAList(Exp * val) {
    expList.push_back(val);
}

void ECMAList::printExp(int lmargin) {
    int expCount = (int)expList.size();

    indent(lmargin);
    cout << "List" << endl;

    if (expCount > 0) {
        for (int i = 0; i < expCount; i++) {
            expList[i] -> printExp(lmargin + INDENT_LEVEL);
        }
    }
}

void ECMAList::addExp(Exp * val) {
    expList.push_back(val);
}

TypeInfo* ECMAList::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    int expCount = (int)expList.size();
    TypeInfo * typeInfo;

    outFile << "\tnew " + to_string(expCount) << endl;

    for (int i = 0; i < expCount; i++) {
        string sti = "\tsti ";

        // (expList[i]에서 자료형에 따라 다르게 처리)
        typeInfo = expList[i] -> codeR(outFile, symbolTable);
        outFile << sti + to_string(i) << endl;
    }

    return new ListType(expCount, typeInfo);
}

// 이항 연산자 클래스
BExp::BExp(string o, Exp *l, Exp *r) {
    if (o == "+=" || o == "-=" || o == "*=" || o == "/=" || o == "%=") {
        char * chr = &o.at(0);
        chr[1] = '\0';
        string oper(chr);
        op = "=";
        left = l;
        right = new BExp(oper, l, r);
    } else {
        op = o;
        left = l;
        right = r;
    }
}

void BExp::printExp(int lmargin) {
    indent(lmargin);
    cout << "Op(" + op + ")" << endl;
    left -> printExp(lmargin + INDENT_LEVEL);
    right -> printExp(lmargin + INDENT_LEVEL);
}

TypeInfo* BExp::codeR(ofstream &outFile, SymbolTable *symbolTable) {

    // 둘 중 하나라도 ID의 주소 값을 가져야 할 경우
    if (op == "=") {
        SymbolEntry * leftSymbolEntry = ((Id*)left) -> codeL(outFile, symbolTable);
        TypeInfo * rightType = right -> codeR(outFile, symbolTable);

        outFile << "\tsto" << endl;
        symbolTable -> changeType(leftSymbolEntry -> name, rightType);
        return new IDType(rightType);
    }

    if (op == "+") {

    }

    TypeInfo * leftType = left -> codeR(outFile, symbolTable);
    TypeInfo * rightType = right -> codeR(outFile, symbolTable);

    if (op == "+") {
        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // INT 또는 Bool 일 경우
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
                    (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tadd" << endl;
            return new IntType();
        }

        // TODO: DOUBLE Type 덧셈
        if (leftType -> type == DOUBLE || rightType -> type == DOUBLE) {
            cout << "double + double not yet" << endl;
            exit(1);
        }

        // string끼리의 덧셈
        if (leftType -> type == STRING && rightType -> type == STRING) {
            // TODO
            cout << "string + string not yet" << endl;
            exit(1);
        }

        // 리스트끼리의 덧셈
        if (leftType -> type == LIST && rightType -> type == LIST) {
            // TODO
            cout << "list + list not yet" << endl;
            exit(1);
        }

        // TODO
        cout << "another + not yet" << endl;
        exit(1);
    } else if (op == "-") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 정수끼리의 뺄셈
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tsub" << endl;
            return new IntType();
        }

        // TODO
        cout << "another - not yet" << endl;
        exit(1);
    } else if (op == "*") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 정수끼리의 곱셈
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tmul" << endl;
            return new IntType();
        }

        // TODO
        cout << "another * not yet" << endl;
        exit(1);
    } else if (op == "/") {
        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 정수끼리의 나눗셈
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tdiv" << endl;
            return new IntType();
        }

        // TODO
        cout << "another / not yet" << endl;
        exit(1);
    } else if (op == "<") {
        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 정수끼리의 비교
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tles" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another < not yet" << endl;
        exit(1);
    } else if (op == "<=") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 정수끼리의 비교
        if (leftType -> type == INT && rightType -> type == INT) {
            outFile << "\tleq" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another <= not yet" << endl;
        exit(1);
    } else if (op == ">") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }


        // 정수끼리의 비교
        if (leftType -> type == INT && rightType -> type == INT) {
            outFile << "\tgrt" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another > not yet" << endl;
        exit(1);
    } else if (op == ">=") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }


        // 정수끼리의 비교
        if (leftType -> type == INT && rightType -> type == INT) {
            outFile << "\tgeq" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another >= not yet" << endl;
        exit(1);
    } else if (op == "==") {
        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 정수끼리의 비교
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tequ" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another == not yet" << endl;
        exit(1);
    } else if (op == "!=") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }


        // 정수끼리의 비교
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tneq" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another != not yet" << endl;
        exit(1);
    } else if (op == "&&") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        // 불리언끼리의 로직
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tand" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another && not yet" << endl;
        exit(1);
    } else if (op == "||") {

        // 타입이 ID이면 ID의 valType으로 변경하여 연산
        if (leftType -> type == ID) {
            leftType = ((IDType*)leftType) -> valTypeInfo;
        }

        if (rightType -> type == ID) {
            rightType = ((IDType*)rightType) -> valTypeInfo;
        }

        
        // 불리언끼리의 로직
        if ((leftType -> type == INT || leftType -> type == BOOL) &&
            (rightType -> type == INT || rightType -> type == BOOL)) {
            outFile << "\tor" << endl;
            return new BoolType();
        }

        // TODO
        cout << "another || not yet" << endl;
        exit(1);
    } if (op == "[]") {
        // 리스트 안에 있는 모든 값은 같은 타입이여야 함
        // 인터프리터가 아니라서 right의 값을 못가져오기 힘듬
        cout << leftType -> type << endl;
        cout << ((IDType*)leftType) -> valTypeInfo -> type << endl;
        cout << rightType -> type << endl;
        if (leftType -> type == ID &&
                (((IDType*)leftType) -> valTypeInfo -> type == LIST) &&
                rightType -> type == INT) {
            outFile << "\tadd" << endl;
            outFile << "\tind" << endl;
            return ((ListType*)((IDType*)leftType) -> valTypeInfo) -> typeInfo;
        }

        // TODO: 에러 처리
        cout << "another [] not yet" << endl;
        exit(1);
    }

    // TODO mod
    cout << "mod not yet" << endl;
    exit(1);
}

// 단항 연산자 클래스
UExp::UExp(string o, Exp * e, int isPre) : op(o), exp(e), isPre(isPre){ }

void UExp::printExp(int lmargin) {
    indent(lmargin);
    cout << "Uop(" + op + ")" << endl;
    exp -> printExp(lmargin + INDENT_LEVEL);
}

TypeInfo* UExp::codeR(ofstream &outFile, SymbolTable *symbolTable) {
    if (op == "()") {
        FuncSymbolEntry * symbolEntry = (FuncSymbolEntry *)symbolTable -> getEntry(((Id*)exp) -> name);
        outFile << "\tmst" << endl;
        outFile << "\tcup " + to_string(symbolEntry -> paramLength) + " " + ((Id*)exp) -> name << endl;
        return new IntType();
    }

    TypeInfo * typeInfo = exp -> codeR(outFile, symbolTable);

    if (op == "&") {
        if (typeInfo -> type == ID) {
            SymbolEntry * entry = symbolTable -> getEntry(((Id*)exp) -> name);
            outFile << "\tpop" << endl;
            outFile << "\tlda " + to_string(entry -> offset) << endl;

            cout << "& not support!" << endl;
            exit(1);
        }
    } else if (op == "-") {

        // 정수와 소수에 대해서만 가능
        if (typeInfo -> type == INT) {
            outFile << "\tneg" << endl;
            return new IntType();
        }

        cout << "-(unary) only INT" << endl;
        exit(1);
    } else if (op == "*") {

        cout << "support yet" << endl;
        exit(1);
    } else if (op == "!") {


        cout << "support yet" << endl;
        exit(1);
    } else if (op == "++" && isPre) {

        cout << "support yet" << endl;
        exit(1);
    } else if (op == "--" && isPre) {

        cout << "support yet" << endl;
        exit(1);
    } else {
        cout << "not support unary!" << endl;
        exit(1);
    }

    cout << "none unary!" << endl;
    exit(1);
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

void IdentifierList::createSymbolTables(SymbolTable *symbolTable) {
    int idCount = (int)identifiers.size();

    if (idCount > 0) {
        for (int i = 0; i < idCount; i++) {
            symbolTable -> setSymbolTableEntry(identifiers[i] -> name, NONE);
        }
    }
}

int IdentifierList::getAmount() {
    return (int)identifiers.size();
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

void FuncDeclarator::code(ofstream &outFile, SymbolTable *symbolTable) {
    outFile << identifier -> name + ": ";
    outFile << "\tssp " + to_string(symbolTable -> currentOffset) << endl;
}

void FuncDeclarator::createSymbolTables(SymbolTable *symbolTable) {
    if (paramList != NULL) {
        paramList -> createSymbolTables(symbolTable);
        symbolTable -> upperSymbolTable -> setFuncSymbolTableEntry(identifier -> name, FUNCTION,
                                               paramList -> getAmount(), symbolTable);
    } else {
        symbolTable -> upperSymbolTable -> setFuncSymbolTableEntry(identifier -> name, FUNCTION, 0, symbolTable);
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

void FuncDecl::code(ofstream &outFile, SymbolTable *symbolTable) {
    FuncSymbolEntry * funcSymbolEntry = (FuncSymbolEntry*)symbolTable -> getEntry(funcDeclarator -> identifier -> name);
    SymbolTable * funcSymbolTable = funcSymbolEntry -> entrySymbolTable;
    funcDeclarator -> code(outFile, funcSymbolTable);

    DeclList * funcDeclList = ((CompoundStatement*)compoundStatement) -> declarationList;
    StatementList * funcStmtList = ((CompoundStatement*)compoundStatement) -> statementList;

    if (funcDeclList != NULL) {
        funcDeclList -> createSymbolTables(funcSymbolTable);
        funcDeclList -> code(outFile, funcSymbolTable);
    }

    if (funcStmtList != NULL) {
        funcStmtList -> code(outFile, funcSymbolTable);
    }
}

int FuncDecl::getDeclAmount() {
    return 1;
}

void FuncDecl::createSymbolTables(SymbolTable *symbolTable) {
    SymbolTable * newSymbolTable = new SymbolTable(symbolTable -> globalSymbolTable, symbolTable);
    funcDeclarator -> createSymbolTables(newSymbolTable);
    ((CompoundStatement*)compoundStatement) -> createSymbolTable(newSymbolTable);
}

typeKind FuncDecl::getType() {
    return FUNCTION;
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

void StatementList::code(ofstream &outFile, SymbolTable *symbolTable) {
    int stmtCount = (int)statements.size();

    if (stmtCount > 0) {
        for (int i = 0; i < stmtCount; i++) {
            statements[i] -> code(outFile, symbolTable);
        }
    }
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

int CompoundStatement::getDeclAmount() {
    return (int)(declarationList -> decls.size());
}

void CompoundStatement::code(ofstream &outFile, SymbolTable *symbolTable) {
    SymbolTable * newSymbolTable = new SymbolTable(symbolTable -> globalSymbolTable, symbolTable);

    outFile << "\tmst" << endl;
    outFile << "\tcup 0 c" << endl;
    outFile << "c: ";
    outFile << "\tssp 2" << endl;

    if (declarationList != NULL) {
        declarationList -> createSymbolTables(newSymbolTable);
        declarationList -> code(outFile, newSymbolTable);
    }

    if (statementList != NULL) {
        statementList -> code(outFile, newSymbolTable);
    }
}

void CompoundStatement::createSymbolTable(SymbolTable * symbolTable) {
    if (declarationList != NULL) {
        declarationList -> createSymbolTables(symbolTable);
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

void ExpStatement::code(ofstream &outFile, SymbolTable * symbolTable) {
    exp -> codeR(outFile, symbolTable);
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

void IfStatement::code(ofstream &outFile, SymbolTable * symbolTable) {
    condition -> codeR(outFile, symbolTable);

    if (elseStatement != NULL) {
        // if else
        outFile << "\tfjp l1" << endl;
        trueStatement -> code(outFile, symbolTable);
        outFile << "\tfjp l2" << endl;
        outFile << "l1: ";
        elseStatement -> code(outFile, symbolTable);
        outFile << "l2: ";
    } else {
        // if
        outFile << "\tfjp l" << endl;
        trueStatement -> code(outFile, symbolTable);
        outFile << "l: ";
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

void WhileStatement::code(ofstream &outFile, SymbolTable * symbolTable) {
    outFile << "l1: ";
    condition -> codeR(outFile, symbolTable);
    outFile << "\tfjp l2" << endl;
    statement -> code(outFile, symbolTable);
    outFile << "\tujp l1" << endl;
    outFile << "l2: " << endl;
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


void ForStatement::code(ofstream &outFile, SymbolTable * symbolTable) {
    initStatement -> code(outFile, symbolTable);
    outFile << "l1: ";
    conditionStatement -> code(outFile, symbolTable);
    outFile << "\tfjp l2" << endl;
    statement -> code(outFile, symbolTable);
    lastExp -> codeR(outFile, symbolTable);
    outFile << "\tujp l1" << endl;
    outFile << "l2: ";

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
// TODO:
void ForInStatement::code(ofstream &outFile, SymbolTable * symbolTable) {

}

// Jump Statement 클래스
JumpStatement::JumpStatement(string n, Exp * r) : name(n), returnExp(r) { }

void JumpStatement::printStatement(int lmargin) {
    indent(lmargin);
    cout << "JumpStatement(" << name << ")" << endl;

    if ((name == "return") && returnExp != NULL) {
        returnExp -> printExp(lmargin + INDENT_LEVEL);
    }
}

void JumpStatement::code(ofstream &outFile, SymbolTable * symbolTable) {
    if (name == "continue") {
        outFile << "\tujp l1" << endl;
    } else if (name == "break") {
        outFile << "\tujp l2" << endl;
    } else if (name == "return" && returnExp != NULL) {
        returnExp -> codeR(outFile, symbolTable);
        outFile << "\tsto 0" << endl;
        outFile << "\tretf" << endl;
    } else if (name == "return") {
        outFile << "\tretp" << endl;
    } else {
        cout << "another jump statement is not support!" << endl;
        exit(1);
    };
}

void indent(int n)
{
    if (n > 0) {
        cout << " ";
        indent(--n);
    }
}
