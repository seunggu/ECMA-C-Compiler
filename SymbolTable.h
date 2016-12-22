//
// Created by seunggu on 2016. 12. 19..
//

#ifndef CPLUS_PRACTICE_SYMBOLTABLE_H
#define CPLUS_PRACTICE_SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "TypeInfo.h"

using namespace std;

class SymbolTable;

// SymbolEntry 클래스
class SymbolEntry {
public:
    string name;
    typeKind type;
    int level; // scope 단위
    int offset; // scope 안에서의 몇번째 인지
};

class NoneSymbolEntry : public SymbolEntry {
public:
    NoneSymbolEntry(string name, typeKind type, int level, int offset);
};

// Int Symbol Entry 클래스
class IntSymbolEntry : public SymbolEntry {
public:
    IntSymbolEntry(string name, typeKind type, int level, int offset);
};

// Double Symbol Entry 클래스
class DoubleSymbolEntry : public SymbolEntry {
public:
    DoubleSymbolEntry(string name, typeKind type, int level, int offset);
};

// Bool Symbol Entry 클래스
class BoolSymbolEntry : public SymbolEntry {
public:
    BoolSymbolEntry(string name, typeKind type, int level, int offset);
};

// String Symbol Entry 클래스
class StringSymbolEntry : public SymbolEntry {
public:
    int vectorLength;

    StringSymbolEntry(string name, typeKind type, int level, int offset, int vectorLength);
};

// List Symbol Entry 클래스
class ListSymbolEntry : public SymbolEntry {
public:
    int vectorLength;
    TypeInfo * typeInfo;

    ListSymbolEntry(string name, typeKind type, int level, int offset, int vectorLength, TypeInfo * typeInfo);
};

// Func Symbol Entry 클래스
class FuncSymbolEntry : public SymbolEntry {
public:
    int paramLength;
    SymbolTable * entrySymbolTable;

    FuncSymbolEntry(string name, typeKind type, int level, int offset, int paramLength, SymbolTable * entrySymbolTable);
};







// Symbol Table 클래스
class SymbolTable {
public:
    int level;
    int currentOffset;
    unordered_map<string, SymbolEntry *> entrys;
    SymbolTable * upperSymbolTable;
    SymbolTable * globalSymbolTable;

    // 생성자
    SymbolTable();
    SymbolTable(SymbolTable * globalSymbolTable, SymbolTable * upperSymbolTable);

    // Entry Get & Set
    int setSymbolTableEntry(string name, typeKind type);
    int setSymbolTableEntry(string name, typeKind type, int vectorLength);
    int setFuncSymbolTableEntry(string name, typeKind type, int paramLength, SymbolTable * entrySymbolTable);
    int setSymbolTableEntry(string name, typeKind type, int vectorLength, TypeInfo * typeInfo);
    void changeType(string name, TypeInfo * typeinfo);
    SymbolEntry* getEntry(string name);

private:
    void changeEntry(string name, SymbolEntry * entry);
};




#endif //CPLUS_PRACTICE_SYMBOLTABLE_H
