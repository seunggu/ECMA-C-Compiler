//
// Created by seunggu on 2016. 12. 22..
//

#ifndef CPLUS_PRACTICE_TYPEINFO_H
#define CPLUS_PRACTICE_TYPEINFO_H

#include <iostream>
#include <vector>

// NONE: 아직 정해지지 않음
enum typeKind {NONE, ID, INT, DOUBLE, BOOL, STRING, LIST, FUNCTION};


using namespace std;

class TypeInfo {
public:
    typeKind type;
};

// ID Type 클래스
class IDType : public TypeInfo {
public:
    TypeInfo * valTypeInfo;

    IDType(TypeInfo * valTypeInfo);
};

// None Type 클래스
class NoneType : public TypeInfo {
public:
    NoneType();
};

// Int Type 클래스
class IntType : public TypeInfo {
public:

    IntType();
};

// Double Type 클래스
class DoubleType : public TypeInfo {
public:
    DoubleType();
};

// Bool Type 클래스
class BoolType : public TypeInfo {
public:
    BoolType();
};

// String Type 클래스
class StringType : public TypeInfo {
public:
    int vectorLength;

    StringType(int vectorLength);
};

// List Type 클래스
class ListType : public TypeInfo {
public:
    int vectorLength;
    TypeInfo * typeInfo;

    ListType(int vectorLength, TypeInfo* typeInfo);
};


#endif //CPLUS_PRACTICE_TYPEINFO_H
