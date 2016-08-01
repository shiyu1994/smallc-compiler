#ifndef GLOBAL_DEFINITION_H_INCLUDED
#define GLOBAL_DEFINITION_H_INCLUDED

#include "Symbol.h"
#include "Type.h"
#include "Instruction.h"
#include <vector>
#include <fstream>

/*
 Define the global definition structures. GlobalDefinition has three subclasses, StructureDefine, ExtVarDefine and Function. Function are defined in a separated file.
 */

class Instruction;

class GlobalDefinition {
protected:
    Symbol* symbol;
public:
    GlobalDefinition(Symbol* symbol) : symbol(symbol) {}
    virtual void Emit(ofstream& os) = 0;
    virtual void Optimize() = 0;
};

class StructDefine : public GlobalDefinition {
public:
    StructDefine(Symbol* structSymbol) : GlobalDefinition(structSymbol) {}
    void Emit(ofstream& os);
    void Optimize() {};
};

class ExtVarDefine : public GlobalDefinition {
private:
    void GenArrayInitializer(Type* type, int& valueConsumed, ofstream& os);
    std::vector<Instruction*>* values;
    std::vector<int>* dimensionSizes;
public:
    ExtVarDefine(Symbol* var, std::vector<Instruction*>* values)
    : GlobalDefinition(var), values(values) {}
    void Emit(ofstream& os);
    void Optimize() {};
};

#endif