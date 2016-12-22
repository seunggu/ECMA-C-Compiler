//
// Created by seunggu on 2016. 12. 22..
//

#include "TypeInfo.h"

// ID Type 클래스
IDType::IDType(TypeInfo * valTypeInfo) : valTypeInfo(valTypeInfo) {
    type = ID;
}

// None Type 클래스
NoneType::NoneType() {
    type = NONE;
}

// Int Type 클래스
IntType::IntType() {
    type = INT;
}

// Double Type 클래스
DoubleType::DoubleType() {
    type = DOUBLE;
}


// Bool Type 클래스
BoolType::BoolType() {
    type = BOOL;
}


// String Type 클래스
StringType::StringType(int vectorLength) : vectorLength(vectorLength) {
    type = STRING;
}


// List Type 클래스
ListType::ListType(int vectorLength, TypeInfo * typeInfo)
        : vectorLength(vectorLength), typeInfo(typeInfo) {
    type = LIST;
}
