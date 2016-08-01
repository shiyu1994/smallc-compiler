#include "SymbolTable.h"
#include "Symbol.h"
#include "Type.h"
#include <vector>
#include <iostream>

/*
 Define methods for symbol table
 */

using namespace std;

//Enter a context
void SymbolTable::EnterScope() {
    currFrame = new SymbolTableFrame(currFrame);
}

//Exit a context
void SymbolTable::ExitScope() {
    currFrame = currFrame->innerFrame;
}

SymbolTable::SymbolTable() {
    SymbolTableFrame* baseFrame = new SymbolTableFrame(NULL);
    Structure* ioParas = new Structure("");
    ioParas->Collect("number", new Int());
    FuncType* ioFunctionType = new FuncType(ioParas, new EmptyType());
    Symbol* readFunctionSymbol = new Symbol("read", true, false, 0);
    readFunctionSymbol->type = ioFunctionType;
    baseFrame->Add(readFunctionSymbol);
    Symbol* writeFunctionSymbol = new Symbol("write", true, false, 0);
    writeFunctionSymbol->type = ioFunctionType;
    baseFrame->Add(writeFunctionSymbol);
    currFrame = new SymbolTableFrame(baseFrame);
}

//Add symbol to symbol table
void SymbolTable::Add(Symbol *symbol) {
    currFrame->Add(symbol);
}

Symbol* SymbolTable::Get(std::string name) {
    return currFrame->Get(name);
}

//A newly defined symbol founded
Symbol* SymbolTable::RegisterSymbol(std::string name, bool isFunction, bool isType, int dimension) {
    return currFrame->RegisterSymbol(name, isFunction, isType, dimension);
}

SymbolTableFrame* SymbolTable::GetCurrFrame() {
    return currFrame;
}

void SymbolTableFrame::Add(Symbol* symbol) {
    symbols.push_back(symbol);
}

//Get symbol from a symbol table frame
Symbol* SymbolTableFrame::Get(std::string name) {
    for(std::vector<Symbol*>::iterator itor = symbols.begin(); itor != symbols.end(); ++itor) {
        if((*itor)->name == name) {
            if(innerFrame != NULL && innerFrame->innerFrame == NULL) {
                (*itor)->isGlobal = true;
            }
            return *itor;
        }
    }
    if(innerFrame == NULL) {
        cout << "Use of undefined symbol " << name << " ";
        return NULL;
    }
    return innerFrame->Get(name);
}

Symbol* SymbolTableFrame::GetInCurrFrame(std::string name) {
    for(std::vector<Symbol*>::iterator itor = symbols.begin(); itor != symbols.end(); ++itor) {
        if((*itor)->name == name) {
            return *itor;
        }
    }
    return NULL;
}

Symbol* SymbolTableFrame::RegisterSymbol(std::string name, bool isFunction, bool isType, int dimension) {
    for(std::vector<Symbol*>::iterator itor = symbols.begin(); itor != symbols.end(); ++itor) {
        if((*itor)->name == name) {
            cout << "Redefinition of symbol " << name << " ";
            return NULL;
        }
    }
    Symbol* newSymbol = new Symbol(name, isFunction, isType, dimension);
    Add(newSymbol);
    if(innerFrame != NULL && innerFrame->innerFrame == NULL) {
        newSymbol->isGlobal = true;
    }
    return newSymbol;
}

SymbolTableFrame::SymbolTableFrame(SymbolTableFrame* innerFrame) : innerFrame(innerFrame) {}