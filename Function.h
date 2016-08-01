#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include "Symbol.h"
#include "BasicBlock.h"
#include "GlobalDefinition.h"
#include <vector>
#include <iostream>
#include <fstream>

/*
 The data structure for Function, it is a subclass of global definitions, which make up the whole module. 
 */

class Function : public GlobalDefinition {
private:
    std::vector<BasicBlock*>* basicBlocks;
public:
    Function(Symbol* functionSymbol, std::vector<BasicBlock*>* basicBlocks) : GlobalDefinition(functionSymbol), basicBlocks(basicBlocks) {}
    void Emit(ofstream& os);
    void PassForBranch();
    void Optimize();
};

#endif