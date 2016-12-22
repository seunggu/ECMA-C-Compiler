//
// Created by seunggu on 2016. 12. 19..
//

#include "SymbolTable.h"

NoneSymbolEntry::NoneSymbolEntry(string name, typeKind type, int level, int offset) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
}

// Int Symbol Entry 클래스
IntSymbolEntry::IntSymbolEntry(string name, typeKind type, int level, int offset) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
}

// Double Symbol Entry 클래스
DoubleSymbolEntry::DoubleSymbolEntry(string name, typeKind type, int level, int offset) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
}

// Bool Symbol Entry 클래스
BoolSymbolEntry::BoolSymbolEntry(string name, typeKind type, int level, int offset) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
}

// String Symbol Entry 클래스
StringSymbolEntry::StringSymbolEntry(string name, typeKind type, int level, int offset, int vectorLength)
        : vectorLength(vectorLength) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
}

// List Symbol Entry 클래스
ListSymbolEntry::ListSymbolEntry(string name, typeKind type, int level, int offset, int vectorLength, TypeInfo * typeInfo)
        : vectorLength(vectorLength), typeInfo(typeInfo) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
}

FuncSymbolEntry::FuncSymbolEntry(string name, typeKind type, int level, int offset, int paramLength, SymbolTable * entrySymbolTable) {
    this -> name = name;
    this -> type = type;
    this -> level = level;
    this -> offset = offset;
    this -> paramLength = paramLength;
    this -> entrySymbolTable = entrySymbolTable;
}











// Symbol Table 클래스
SymbolTable::SymbolTable()
        : level(0), currentOffset(1), globalSymbolTable(this), upperSymbolTable(NULL) { }

SymbolTable::SymbolTable(SymbolTable * globalSymbolTable, SymbolTable * upperSymbolTable)
        : currentOffset(3), globalSymbolTable(globalSymbolTable), upperSymbolTable(upperSymbolTable) {
    level = upperSymbolTable -> level + 1;
}

int SymbolTable::setSymbolTableEntry(string name, typeKind type) {
    SymbolEntry * entry;

    if (type == INT) {
        entry = new IntSymbolEntry(name, type, level, currentOffset);
    } else if (type == DOUBLE) {
        entry = new DoubleSymbolEntry(name, type, level, currentOffset);
    } else if (type == BOOL) {
        entry = new BoolSymbolEntry(name, type, level, currentOffset);
    } else {
        entry = new NoneSymbolEntry(name, type, level, currentOffset);
    }

    entrys[name] = entry;
    currentOffset += 1;
    return entry -> offset;
}

int SymbolTable::setSymbolTableEntry(string name, typeKind type, int vectorLength) {
    SymbolEntry * entry = new StringSymbolEntry(name, type, level, currentOffset, vectorLength);
    entrys[name] = entry;
    currentOffset += 1;
    return entry -> offset;
}

int SymbolTable::setFuncSymbolTableEntry(string name, typeKind type, int paramLength, SymbolTable * entrySymbolTable) {
    SymbolEntry * entry = new FuncSymbolEntry(name, type, level, currentOffset, paramLength, entrySymbolTable);
    entrys[name] = entry;
    currentOffset += 1;
    return entry -> offset;
}

int SymbolTable::setSymbolTableEntry(string name, typeKind type, int vectorLength, TypeInfo * typeInfo) {
    SymbolEntry * entry = new ListSymbolEntry(name, type, level, currentOffset, vectorLength, typeInfo);
    entrys[name] = entry;
    currentOffset += 1;
    return entry -> offset;
}

SymbolEntry* SymbolTable::getEntry(string name) {
    SymbolTable * symbolTable = this;

    while (symbolTable != NULL) {

        if (symbolTable -> entrys[name] != NULL) {
            return symbolTable -> entrys[name];
        } else {
            symbolTable = symbolTable -> upperSymbolTable;
            continue;
        }
    }

    cout << name + " is not declared!" << endl;
    exit(1);
}

void SymbolTable::changeType(string name, TypeInfo * typeInfo) {
    SymbolEntry * entry = getEntry(name);
    SymbolEntry * changedEntry;

    if (typeInfo -> type == ID && (((IDType*)typeInfo) -> valTypeInfo) -> type == INT) {
        changedEntry = new IntSymbolEntry(name, INT, entry -> level, entry -> offset);
    } else if (typeInfo -> type == ID && (((IDType*)typeInfo) -> valTypeInfo) -> type == BOOL) {
        changedEntry = new BoolSymbolEntry(name, BOOL, entry -> level, entry -> offset);
    } else if (typeInfo -> type == ID && (((IDType*)typeInfo) -> valTypeInfo) -> type == DOUBLE) {
        changedEntry = new DoubleSymbolEntry(name, DOUBLE, entry -> level, entry -> offset);
    } else if (typeInfo -> type == ID && (((IDType*)typeInfo) -> valTypeInfo) -> type == STRING) {
        changedEntry = new StringSymbolEntry(name, STRING, entry -> level, entry -> offset,
                                             ((StringType*)((IDType*)typeInfo) -> valTypeInfo) -> vectorLength);
    } else if (typeInfo -> type == ID && (((IDType*)typeInfo) -> valTypeInfo) -> type == LIST) {
        changedEntry = new ListSymbolEntry(name, LIST, entry -> level, entry -> offset,
                                           ((ListType*)((IDType*)typeInfo) -> valTypeInfo) -> vectorLength,
                ((ListType*)((IDType*)typeInfo) -> valTypeInfo) -> typeInfo);
    } else if (typeInfo -> type == INT) {
        changedEntry = new IntSymbolEntry(name, INT, entry -> level, entry -> offset);
    } else if (typeInfo -> type == BOOL) {
        changedEntry = new BoolSymbolEntry(name, BOOL, entry -> level, entry -> offset);
    } else if (typeInfo -> type == DOUBLE) {
        changedEntry = new DoubleSymbolEntry(name, DOUBLE, entry -> level, entry -> offset);
    } else if (typeInfo -> type == STRING) {
        changedEntry = new StringSymbolEntry(name, STRING, entry -> level, entry -> offset, ((StringType*)typeInfo) -> vectorLength);
    } else if (typeInfo -> type == LIST) {
        changedEntry = new ListSymbolEntry(name, LIST, entry -> level, entry -> offset, ((ListType*)typeInfo) -> vectorLength,
                ((ListType*)typeInfo) -> typeInfo);
    } else {
        cout << "this type not support!" << endl;
        exit(1);
    }

    changeEntry(name, changedEntry);
}

void SymbolTable::changeEntry(string name, SymbolEntry * entry) {
    SymbolTable * symbolTable = this;

    while (symbolTable != NULL) {
        if (entrys[name] != NULL) {
            entrys[name] = entry;
            break;
        } else {
            symbolTable = symbolTable -> upperSymbolTable;
            continue;
        }
    }
}