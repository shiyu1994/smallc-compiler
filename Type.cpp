#include "Type.h"
#include <iostream>
#include <vector>
#include <fstream>

/*
 Define constructors for types
 */


using namespace std;

void Structure::Collect(std::string field, Type *type) {
    elementTypes.push_back(new NameTypePair(field, type));
}

Type* Structure::getElementType(std::string field) {
    for(std::vector<NameTypePair*>::iterator itor = elementTypes.begin(); itor != elementTypes.end(); ++itor) {
        //os << (*itor)->name << endl;
        if(field == (*itor)->name) {
            return (*itor)->type;
        }
    }
    return new EmptyType();
}

void Int::Emit(ofstream& os) {
    os << "i32";
}

void Structure::Emit(ofstream& os) {
    os << "%struct." << typeName;
}

void Array::Emit(ofstream& os) {
    os << "[" << length << " x ";
    elementType->Emit(os);
    os << "]";
}

void Bool::Emit(ofstream& os) {
    os << "i1";
}

void MetaType::Emit(ofstream& os) {}

void TupleType::Emit(ofstream& os) {}

void FuncType::Emit(ofstream& os) {}

void EmptyType::Emit(ofstream& os) {}