#include "Module.h"
#include <iostream>
#include <fstream>

using namespace std;

/*
 Define functions for Module class, this is the entrance of code generation
 */

//Add global definitions to a module
void Module::Add(GlobalDefinition *definition) {
    definitions.push_back(definition);
}

//Emit every global definiton, also prepare the I/O
void Module::Emit(ofstream& os) {
    os << "@.str = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1" << endl;
    os << "@.str1 = private unnamed_addr constant [4 x i8] c\"%d\\0A\\00\", align 1" << endl;
    for(int i = 0; i < definitions.size(); ++i) {
        definitions[i]->Emit(os);
    }
    os << "declare i32 @scanf(i8*, ...)" << endl;
    os << "declare i32 @printf(i8*, ...)" << endl;
}

void Module::Optimize() {
    for(int i = 0; i < definitions.size(); ++i) {
        definitions[i]->Optimize();
    }
}