#include "Function.h"
#include "Type.h"
#include "BasicBlock.h"
#include <iostream>
#include <fstream>

/*
 This file defines methods for Function class, including emitting intermediate code to .ll file, resolving labels for basic blocks, and optimization.
 */

void Function::Emit(ofstream& os) {
    FuncType* funcType = (FuncType*)symbol->type;
    os << "define ";
    funcType->returnType->Emit(os);
    os << " @" << symbol->name << "(";
    Structure* paraTypes = funcType->paraType;
    Instruction::counter = 0;
    if(paraTypes->elementTypes.size() > 0) {
        for(int i = 0; i < paraTypes->elementTypes.size() - 1; ++i) {
            paraTypes->elementTypes[paraTypes->elementTypes.size() - 1 - i]->type->Emit(os);
            os << " %" << paraTypes->elementTypes[paraTypes->elementTypes.size() - 1 - i]->name << ",";
        }
        paraTypes->elementTypes.front()->type->Emit(os);
        os << " %" << paraTypes->elementTypes.front()->name;
    }
    os << ") {" << endl;
    PassForBranch();
    for(int i = 0; i < basicBlocks->size(); ++i) {
        (*basicBlocks)[i]->Emit(os);
    }
    os << "}" << endl;
}

void Function::PassForBranch() {
    for(int i = 0; i < basicBlocks->size(); ++i) {
        (*basicBlocks)[i]->PassForBranch();
    }
}

//First search for all the useful instructions, then clean the useless instructions.
void Function::Optimize() {
    for(int i = 0; i < basicBlocks->size(); ++i) {
        (*basicBlocks)[i]->Optimize();
    }
    for(int i = 0; i < basicBlocks->size(); ++i) {
        (*basicBlocks)[i]->Clean();
    }
}
