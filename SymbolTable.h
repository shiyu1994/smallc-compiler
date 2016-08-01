#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED

#include "Symbol.h"
#include <vector>
#include <string>

/*
 Define data structures for symbol table
 */

using namespace  std;

class Symbol;
class SymbolTableFrame;
class SymbolTable {
private:
    SymbolTableFrame* currFrame;
public:
    void Add(Symbol* symbol);
    Symbol* Get(std::string name);
    SymbolTable();
    void EnterScope();
    void ExitScope();
    void DumpCurrFrameTo(Symbol* structSymbol);
    Symbol* RegisterSymbol(std::string name, bool isFunction, bool isType, int dimension);
    SymbolTableFrame* GetCurrFrame();
};

class SymbolTableFrame {
friend class SymbolTable;
private:
    SymbolTableFrame* innerFrame;
public:
    string owner;
    std::vector<Symbol*> symbols;
    SymbolTableFrame(SymbolTableFrame* innerFrame);
    void Add(Symbol* symbol);
    Symbol* Get(std::string name);
    Symbol* GetInCurrFrame(std::string name);
    Symbol* RegisterSymbol(std::string name, bool isFunction, bool isType, int dimension);
};

#endif