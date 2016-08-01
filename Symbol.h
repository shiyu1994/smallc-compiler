#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include <string>
#include <vector>
#include "Type.h"
#include "SymbolTable.h"

/*
 Define the symbol data structure
 */


//Symbol contains type and name for a identifier
class SymbolTableFrame;
class Symbol {
    friend class SymbolTable;
private:
    SymbolTableFrame* fieldSymbols;
public:
    std::string name;
    const bool isFunction;
    const bool isType;
    int dimension;
    bool isGlobal;
    bool sideEffectFunction;
    Type* type;
    Symbol(std::string name, bool isFunction, bool isType, int dimension);
    void SetFieldSymbols(SymbolTableFrame* fieldSymbols) {
        this->fieldSymbols = fieldSymbols;
    }
    SymbolTableFrame* GetFieldSymbols() {
        return fieldSymbols;
    }
};

class TypeSymbol : public Symbol {
public:
    TypeSymbol(std::string name);
};

class FunctionSymbol : public Symbol {
public:
    FunctionSymbol(std::string name);
};

class VarSymbol : public Symbol {
public:
    VarSymbol(std::string name);
};

#endif