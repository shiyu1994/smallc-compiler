#include <iostream>
#include <vector>
#include "GlobalDefinition.h"
#include "Type.h"
#include <fstream>

using namespace std;

/*
 Define methods for generating global definition structure. Including generating initializations for global variables, and emit intermediate code for global variable define and struct define. 
 */

void ExtVarDefine::Emit(ofstream& os) {
    os << "@" << symbol->name << " = global ";
    GenArrayInitializer(symbol->type, *new int(0), os);
    os << endl;
}

void ExtVarDefine::GenArrayInitializer(Type* type, int &valueConsumed, ofstream& os) {
    type->Emit(os);
    if(valueConsumed < values->size()) {
        if(type->isStruct) {
            Structure* structType = (Structure*) type;
            os << " { ";
            for(int i = 0; i < structType->elementTypes.size() - 1; ++i) {
                GenArrayInitializer(structType->elementTypes[i]->type, valueConsumed, os);
                os << ", ";
            }
            GenArrayInitializer(structType->elementTypes[structType->elementTypes.size() - 1]->type, valueConsumed, os);
            os << " }";
        }
        else if(type->isArray) {
            Array* arrayType = (Array*) type;
            os << " [ ";
            for(int i = 0; i < arrayType->length - 1; ++i) {
                GenArrayInitializer(arrayType->elementType, valueConsumed, os);
                os << ", ";
            }
            GenArrayInitializer(arrayType->elementType, valueConsumed, os);
            os << " ]";
        }
        else {
            os << " ";
            if(valueConsumed < values->size()) {
                os << ((NumInstruction*)((*values)[values->size() - 1 - valueConsumed]))->num;
                ++valueConsumed;
            }
        }
    }
    else {
        if(!type->isArray && !type->isStruct) {
            os << " 0";
        }
        else {
            os << " zeroinitializer";
        }
    }
}

void StructDefine::Emit(ofstream& os) {
    os << "%struct." << symbol->name << " = type { ";
    Structure* structType = (Structure*)(((MetaType*)symbol->type)->containType);
    if(structType->elementTypes.size() > 0) {
        for(int i = 0; i < structType->elementTypes.size() - 1; ++i) {
            structType->elementTypes[i]->type->Emit(os);
            os << ", ";
        }
        structType->elementTypes.back()->type->Emit(os);
    }
    os << " } " << endl;
}