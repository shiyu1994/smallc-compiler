#include "ParseTree.h"
#include "Instruction.h"
#include "Module.h"
#include "Function.h"
#include "BasicBlock.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/*
 This file defines Gen() functions and other auxilary functions used in code genreation. 
 For each production, we have a Gen() function, and the corresponding productions are commented right above each function.
 Each Gen() function for statements and expressions needs to check whether the current basic block has been closed, if so a new one should be created.
 */

Module* ParseTree::module = new Module();

//PROGRAM : EXTDEFS
void PROGRAM::Gen() {
    extdefs->Gen();
}

void PROGRAM::Optimize() {
    module->Optimize();
}

//EXTDEFS : EXTDEF EXTDEFS
void EXTDEFS1::Gen() {
    extdef->Gen();
    extdefs->Gen();
}

//EXTDEFS :
void EXTDEFS2::Gen() {}

//EXTDEF : SPEC EXTVARS SEMI
void EXTDEF1::Gen() {
    spec->Gen();
    extvars->Gen();
}

//EXTDEF : SPEC FUNC STMTBLOCK
void EXTDEF2::Gen() {
    std::vector<BasicBlock*>* basicBlocks = new std::vector<BasicBlock*>();
    basicBlocks->push_back(new BasicBlock("entry"));
    Structure* paras = ((FuncType*)func->name->symbol->type)->paraType;
    for(int i = 0; i < paras->elementTypes.size(); ++i) {
        Alloca* alloca = new Alloca(paras->elementTypes[paras->elementTypes.size() - 1 - i]->type);
        basicBlocks->back()->Add(alloca);
        Symbol* symbol = new Symbol(paras->elementTypes[paras->elementTypes.size() - 1 - i]->name, false, false, 0);
        symbol->type = paras->elementTypes[paras->elementTypes.size() - 1 - i]->type;
        Store* store = new Store(alloca, new NameInstruction(symbol));
        basicBlocks->back()->Add(store);
    }
    vector<Symbol*>* paraSymbols = func->CollectParaSymbols();
    for(int i = 0; i < paraSymbols->size(); ++i) {
        char* tempName = new char[10];
        sprintf(tempName, "%d", (int)paraSymbols->size() - i);
        (*paraSymbols)[i]->name = tempName;
    }
    stmtblock->GenBasicBlocks(basicBlocks);
    Function* function = new Function(func->GetSymbol(), basicBlocks);
    module->Add(function);
}

//EXTVARS : DEC
void EXTVARS1::Gen() {
    dec->Gen();
}

//EXTVARS : DEC COMMA EXTVARS
void EXTVARS2::Gen() {
    dec->Gen();
    extvars->Gen();
}

//EXTVARS :
void EXTVARS3::Gen() {}

//SPEC : TYPE
void SPEC1::Gen() {}

//SPEC : STSPEC
void SPEC2::Gen() {
    stspec->Gen();
}

//STSPEC : STRUCT OPTTAG LC DEFS RC
void STSPEC1::Gen() {
    StructDefine* structDefine = new StructDefine(opttag->GetSymbol());
    module->Add(structDefine);
}

//STSPEC : STRUCT ID
void STSPEC2::Gen() {}

//OPTTAG : ID
void OPTTAG1::Gen() {}

//OPTTAG :
void OPTTAG2::Gen() {}

void VAR::GenInits(Type *varType, Instruction* address, std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks,
                   int &counter) {
    if(counter >= initValues->size()) {
        return;
    }
    if(varType->isArray) {
        Array* arrayType = (Array*)varType;
        for(int i = 0; i < arrayType->length; ++i) {
            if(counter < initValues->size()) {
                GetElementPtr* elementPtr = new GetElementPtr(address, new NumInstruction(i), arrayType);
                basicBlocks->back()->Add(elementPtr);
                GenInits(arrayType->elementType, elementPtr, initValues, basicBlocks, counter);
            }
        }
    }
    else if(varType->isStruct) {
        Structure* structType = (Structure*)varType;
        for(int i = 0; i < structType->elementTypes.size(); ++i) {
            if(counter < initValues->size()) {
                GetElementPtr* elementPtr = new GetElementPtr(address, new NumInstruction(i));
                basicBlocks->back()->Add(elementPtr);
                GenInits(structType->elementTypes[i]->type, elementPtr, initValues, basicBlocks, counter);
            }
        }
    }
    else {
        if(address->type->typeName != (*initValues)[initValues->size() - 1 - counter]->type->typeName) {
            cout << "Cannot initialize " << address->type->typeName << " with " <<
            (*initValues)[initValues->size() - 1 - counter++]->type->typeName << "." << endl;
        }
        basicBlocks->back()->Add(new Store(address, (*initValues)[initValues->size() - 1 - counter++]));
    }
}

//VAR : ID
void VAR1::Gen(std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks) {
    if(basicBlocks == NULL) {
        ExtVarDefine* firstDefine = new ExtVarDefine(name->symbol, initValues);
        module->Add(firstDefine);
    }
    else {
        Alloca* address = new Alloca(name->symbol);
        basicBlocks->back()->Add(address);
        VAR::GenInits(name->symbol->type, new NameInstruction(name->symbol), initValues, basicBlocks, *new int(0));
    }
}

void VAR1::Gen() {}

Symbol* VAR1::GetSymbol() {
    return name->symbol;
}

//VAR : VAR LB INT RB
void VAR2::Gen(std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks) {
    var->Gen(initValues, basicBlocks);
}

Symbol* VAR2::GetSymbol() {
    return var->GetSymbol();
}

void VAR2::Gen() {}

//FUNC : ID LP PARAS RP
void FUNC::Gen() {
    
}

vector<Symbol*>* FUNC::CollectParaSymbols() {
    return paras->CollectParaSymbols();
}

Symbol* FUNC::GetSymbol() {
    return name->symbol;
}

//PARAS : PARA COMMA PARAS
void PARAS1::Gen() {}

vector<Symbol*>* PARAS1::CollectParaSymbols() {
    vector<Symbol*>* symbols = paras->CollectParaSymbols();
    symbols->push_back(para->GetSymbol());
    
    return symbols;
}

//PARAS : PARA
void PARAS2::Gen() {}

vector<Symbol*>* PARAS2::CollectParaSymbols() {
    vector<Symbol*>* symbols = new vector<Symbol*>;
    symbols->push_back(para->GetSymbol());
    
    return symbols;
}

//PARAS :
void PARAS3::Gen() {}

vector<Symbol*>* PARAS3::CollectParaSymbols() {
    return new vector<Symbol*>;
}

//PARA : SPEC VAR
void PARA::Gen() {}

Symbol* PARA::GetSymbol() {
    return var->GetSymbol();
}

//STMTBLOCK LC DEFS STMTS RC
void STMTBLOCK::GenBasicBlocks(std::vector<BasicBlock*>* basicBlocks,
                               BasicBlock* next,
                               BasicBlock* cont,
                               BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        BasicBlock* basicBlock = new BasicBlock();
        basicBlocks->push_back(basicBlock);
    }
    defs->Gen(basicBlocks);
    stmts->Gen(basicBlocks, next, cont, breakTo);
}

//STMTS : STMT STMTS
void STMTS1::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        BasicBlock* basicBlock = new BasicBlock();
        basicBlocks->push_back(basicBlock);
    }
    BasicBlock* nextStep = new BasicBlock();
    stmt->Gen(basicBlocks, nextStep, cont, breakTo);
    if(basicBlocks->back()->IsClosed()) {
        //UncondBranch* branch = new UncondBranch(nextStep);
        //basicBlocks->back()->Add(branch);
        basicBlocks->push_back(nextStep);
    }
    stmts->Gen(basicBlocks, next, cont, breakTo);
}

//STMTS :
void STMTS2::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {}

//STMT : EXP SEMI
void STMT1::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    exp->Gen(basicBlocks);
}

//STMT : STMTBLOCK
void STMT2::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    stmtblock->GenBasicBlocks(basicBlocks, next, cont, breakTo);
}

//STMT : RETURN EXP SEMI
void STMT3::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    Instruction* returnExp = exp->Gen(basicBlocks);
    basicBlocks->back()->Add(new Return(returnExp, returnExp->type));
    basicBlocks->back()->Close();
}

//STMT : IF LP EXP RP STMT ESTMT
void STMT4::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    BasicBlock* thenBasicBlock = new BasicBlock();
    BasicBlock* elseBasicBlock = new BasicBlock();
    if(!estmt->isEmpty)
        exp->Gen(basicBlocks, false, thenBasicBlock, elseBasicBlock);
    else
        exp->Gen(basicBlocks, false, thenBasicBlock, next);
    basicBlocks->back()->Close();
    basicBlocks->push_back(thenBasicBlock);
    stmt->Gen(basicBlocks, next, cont, breakTo);
    if(next != NULL && !estmt->isEmpty) {
        UncondBranch* branch = new UncondBranch(next);
        basicBlocks->back()->Add(branch);
    }
    basicBlocks->back()->Close();
    basicBlocks->push_back(elseBasicBlock);
    estmt->Gen(basicBlocks, next, cont, breakTo);
    /*if(next != NULL) {
        UncondBranch* branch = new UncondBranch(next);
        basicBlocks->back()->Add(branch);
        basicBlocks->back()->Close();
    }*/
    basicBlocks->back()->Close();
}

//STMT : FOR LP FOREXP SEMI FOREXP SEMI FOREXP RP STMT
void STMT5::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    BasicBlock* checkCondition = new BasicBlock();
    BasicBlock* loopBody = new BasicBlock();
    BasicBlock* increment = new BasicBlock();
    forexp1->Gen(basicBlocks);
    /*UncondBranch* branch = new UncondBranch(checkCondition);
    basicBlocks->back()->Add(branch);
    basicBlocks->back()->Close();*/
    basicBlocks->push_back(checkCondition);
    forexp2->Gen(basicBlocks, loopBody, next);
    basicBlocks->back()->Close();
    basicBlocks->push_back(loopBody);
    stmt->Gen(basicBlocks, increment, increment, next);
    UncondBranch* branchInc = new UncondBranch(increment);
    basicBlocks->back()->Add(branchInc);
    basicBlocks->back()->Close();
    basicBlocks->push_back(increment);
    forexp3->Gen(basicBlocks, checkCondition, NULL);
    basicBlocks->back()->Close();
}

//STMT : CONT SEMI
void STMT6::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    if(cont == NULL) {
        cout << "Line " << lineNumber << "continue statment can only be used in loops." << endl;
    }
    basicBlocks->back()->Add(new UncondBranch(cont));
    basicBlocks->back()->Close();
}

//STMT : BREAK SEMI
void STMT7::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    if(breakTo == NULL) {
        cout << "Line " << lineNumber << "break statment can only be used in loops." << endl;
    }
    basicBlocks->back()->Add(new UncondBranch(breakTo));
    basicBlocks->back()->Close();
}

//ESTMT : ELSE STMT
void ESTMT1::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {
    if(basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    stmt->Gen(basicBlocks, next, cont, breakTo);
}

//ESTMT :
void ESTMT2::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* next, BasicBlock* cont, BasicBlock* breakTo) {}

//DEFS : DEF DEFS
void DEFS1::Gen(std::vector<BasicBlock*>* basicBlocks) {
    def->Gen(basicBlocks);
    defs->Gen(basicBlocks);
}

//DEFS :
void DEFS2::Gen(std::vector<BasicBlock*>* basicBlocks) {}

//DEF : SPEC DECS SEMI
void DEF::Gen(std::vector<BasicBlock*>* basicBlocks) {
    decs->Gen(basicBlocks);
}

//DECS : DEC COMMA DECS
void DECS1::Gen(std::vector<BasicBlock*>* basicBlocks) {
    dec->Gen(basicBlocks);
    decs->Gen(basicBlocks);
}

//DECS : DEC
void DECS2::Gen(std::vector<BasicBlock*>* basicBlocks) {
    dec->Gen(basicBlocks);
}

//DEC : VAR
void DEC1::Gen(std::vector<BasicBlock*>* basicBlocks) {
    var->Gen(new vector<Instruction*>(), basicBlocks);
}

//DEC : VAR ASSIGNOP INIT
void DEC2::Gen(std::vector<BasicBlock*>* basicBlocks) {
    var->Gen(init->Gen(basicBlocks), basicBlocks);
}

//INIT : EXP
vector<Instruction*>* INIT1::Gen(vector<BasicBlock*>* basicBlocks) {
    vector<Instruction*>* arg = new vector<Instruction*>;
    arg->push_back(exp->Gen(basicBlocks));
    
    return arg;
}

//INIT LC ARGS RC
vector<Instruction*>* INIT2::Gen(vector<BasicBlock*>* basicBlocks) {
    return args->Gen(basicBlocks);
}

//FOREXP : EXP
void FOREXP1::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* trueList, BasicBlock* falseList) {
    exp->Gen(basicBlocks, false, trueList, falseList);
}

//FOREXP :
void FOREXP2::Gen(std::vector<BasicBlock*>* basicBlocks, BasicBlock* trueList, BasicBlock* falseList) {}

//EXP : EXP BINARYOP EXP
Instruction* EXP1::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    string operation = op->op;
    Instruction* result;
    if(operation == "==" || operation == "!=" || operation == "<" || operation == ">" || operation == ">=" || operation == "<=") {
        result = new BinaryOperation(op->op, exp1->Gen(basicBlocks), exp2->Gen(basicBlocks), new Bool());
        basicBlocks->back()->Add(result);
        result = new ZeroExtension(result);
    }
    else {
        result = new BinaryOperation(op->op, exp1->Gen(basicBlocks), exp2->Gen(basicBlocks), new Int());
    }
    basicBlocks->back()->Add(result);
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                result = new BinaryOperation("!=", result, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(result);
            }
            result = new Branch(result, trueList, falseList);
        }
        else {
            result = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(result);
        basicBlocks->back()->Close();
    }
    return result;
}

//EXP : UNARYOP EXP
Instruction* EXP2::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    string operation = op->op;
    Instruction* result;
    if(operation == "!") {
        Instruction* expGen = exp->Gen(basicBlocks);
        result = new BinaryOperation("==", expGen, new NumInstruction(0), new Int());
        basicBlocks->back()->Add(result);
        result = new ZeroExtension(result);
        basicBlocks->back()->Add(result);
    }
    else if (operation == "~") {
        Instruction* expGen = exp->Gen(basicBlocks);
        result = new BinaryOperation("^", expGen, new NumInstruction(-1), new Int());
        basicBlocks->back()->Add(result);
    }
    else if(operation == "++") {
        Instruction* expGen = exp->Gen(basicBlocks);
        result = new BinaryOperation("+", expGen, new NumInstruction(1), new Int());
        basicBlocks->back()->Add(result);
        basicBlocks->back()->Add(new Store(exp->Gen(basicBlocks, true), result));
    }
    else {
        Instruction* expGen = exp->Gen(basicBlocks);
        result = new BinaryOperation("-", expGen, new NumInstruction(1), new Int());
        basicBlocks->back()->Add(result);
        basicBlocks->back()->Add(new Store(exp->Gen(basicBlocks, true), result));
    }
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                result = new BinaryOperation("!=", result, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(result);
            }
            result = new Branch(result, trueList, falseList);
        }
        else {
            result = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(result);
        basicBlocks->back()->Close();
    }
    return result;
}

//EXP : '-' EXP
Instruction* EXP3::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    Instruction* result = new BinaryOperation("-", new NumInstruction(0), exp->Gen(basicBlocks), new Int());
    basicBlocks->back()->Add(result);
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                result = new BinaryOperation("!=", result, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(result);
            }
            result = new Branch(result, trueList, falseList);
        }
        else {
            result = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(result);
        basicBlocks->back()->Close();
    }
    return result;
}

//EXP : LP EXP RP
Instruction* EXP4::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    return exp->Gen(basicBlocks, leftVal, trueList, falseList);
}

//EXP : ID LP ARGS RP
Instruction* EXP5::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    bool leftValue;
    if(name->symbol->name == "read") {
        leftValue = true;
    }
    else {
        leftValue = false;
    }
    vector<Instruction*>* arguments = args->Gen(basicBlocks, leftValue);
    Structure* paraTypes = (Structure*)(((FuncType*)name->symbol->type)->paraType);
    if(arguments->size() > paraTypes->elementTypes.size()) {
        cout << "Line " << lineNumber << " Too many arguments for function " << name->symbol->name << "." << endl;
    }
    else if(arguments->size() < paraTypes->elementTypes.size()) {
        cout << "Line " << lineNumber << " Too few arguments for function " << name->symbol->name << "." << endl;
    } else {
        for(int i = 0; i < arguments->size(); ++i) {
            if((*arguments)[i]->type->typeName != paraTypes->elementTypes[i]->type->typeName) {
                cout << "Line " << lineNumber << " the " << arguments->size() - 1 - i
                << "th argument has incosistent type for function " << name->symbol->name << endl;
            }
        }
    }
    
    Instruction* result = new FunctionCall(new NameInstruction(name->symbol), arguments,
                                                  ((FuncType*)name->symbol->type)->returnType);
    
    basicBlocks->back()->Add(result);
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                result = new BinaryOperation("!=", result, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(result);
            }
            result = new Branch(result, trueList, falseList);
        }
        else {
            result = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(result);
        basicBlocks->back()->Close();
    }
    return result;
}

//EXP : ID ARRS
Instruction* EXP6::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    Instruction* result = arrs->Gen(new NameInstruction(name->symbol), (Array*)name->symbol->type, basicBlocks);
    Instruction* reference = result;
    if(!leftVal) {
        reference = new Load(result);
        basicBlocks->back()->Add(reference);
    }
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                reference = new BinaryOperation("!=", reference, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(reference);
            }
            reference = new Branch(reference, trueList, falseList);
        }
        else {
            reference = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(reference);
        basicBlocks->back()->Close();
    }
    if(leftVal) {
        return result;
    }
    else {
        return reference;
    }
}

//EXP : EXP DOT ID
Instruction* EXP7::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    Instruction* result = new GetElementPtr(exp->Gen(basicBlocks, true), new NameInstruction(name->symbol));
    basicBlocks->back()->Add(result);
    Instruction* reference = result;
    if(!leftVal) {
        reference = new Load(result);
        basicBlocks->back()->Add(reference);
    }
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                reference = new BinaryOperation("!=", reference, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(reference);
            }
            reference = new Branch(reference, trueList, falseList);
        }
        else {
            reference = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(reference);
        basicBlocks->back()->Close();
    }
    if(leftVal) {
        return result;
    }
    else {
        return reference;
    }
}

//EXP : INT
Instruction* EXP8::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    Instruction* result = new NumInstruction(num->num);
    Instruction* branch;
    if(basicBlocks != NULL) {
        basicBlocks->back()->Add(result);
    }
    if(trueList != NULL) {
        if(falseList != NULL) {
            if(result->type->isInt) {
                branch = new BinaryOperation("!=", result, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(branch);
            }
            branch = new Branch(branch, trueList, falseList);
        }
        else {
            branch = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(branch);
        basicBlocks->back()->Close();
    }
    return result;
}

//EXP : ID ARRS ASSIGNOP EXP
Instruction* EXP9::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
               BasicBlock* trueList,
               BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    string assignOp = op;
    Instruction* address = arrs->Gen(new NameInstruction(name->symbol), (Array*)name->symbol->type, basicBlocks);
    Instruction* value = new Load(address);
    basicBlocks->back()->Add(value);
    Instruction* assignOperand = exp->Gen(basicBlocks);
    if(assignOp == "+=") {
        assignOperand = new BinaryOperation("+", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "-=") {
        assignOperand = new BinaryOperation("-", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "*=") {
        assignOperand = new BinaryOperation("*", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "/=") {
        assignOperand = new BinaryOperation("/", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "&=") {
        assignOperand = new BinaryOperation("&", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "^=") {
        assignOperand = new BinaryOperation("^", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "|=") {
        assignOperand = new BinaryOperation("|", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == "<<=") {
        assignOperand = new BinaryOperation("<<", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    else if(assignOp == ">>=") {
        assignOperand = new BinaryOperation(">>", value, assignOperand, new Int());
        basicBlocks->back()->Add(assignOperand);
    }
    Store* store = new Store(address, assignOperand);
    basicBlocks->back()->Add(store);
    if(trueList != NULL) {
        Instruction* branch;
        if(falseList != NULL) {
            if(address->type->isInt) {
                branch = new BinaryOperation("!=", address, new NumInstruction(0), new Bool());
                basicBlocks->back()->Add(branch);
            }
            branch = new Branch(branch, trueList, falseList);
        }
        else {
            branch = new UncondBranch(trueList);
        }
        basicBlocks->back()->Add(branch);
        basicBlocks->back()->Close();
    }
    return address;
}

//EXP DOT ID ASSIGNOP EXP
Instruction* EXP10::Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal,
                BasicBlock* trueList,
                BasicBlock* falseList) {
    if(basicBlocks != NULL && basicBlocks->back()->IsClosed()) {
        basicBlocks->push_back(new BasicBlock());
    }
    Instruction* assignOperand = exp2->Gen(basicBlocks);
    Instruction* nameInstruction = new NameInstruction(name->symbol);
    Instruction* address = new GetElementPtr(exp1->Gen(basicBlocks, true), nameInstruction);
    basicBlocks->back()->Add(address);
    Store* store = new Store(address, assignOperand);
    basicBlocks->back()->Add(store);
    return address;
}

//ARRS : LB EXP RB ARRS
Instruction* ARRS1::Gen(Instruction* address, Type* arrayType, vector<BasicBlock*>* basicBlocks) {
    Instruction* index = exp->Gen(basicBlocks);
    Instruction* getElem = new GetElementPtr(address, index, (Array*)arrayType);
    basicBlocks->back()->Add(getElem);
    return arrs->Gen(getElem, ((Array*)arrayType)->elementType, basicBlocks);
}

//ARRS :
Instruction* ARRS2::Gen(Instruction* address, Type* arrayType, vector<BasicBlock*>* basicBlocks) {
    if(address->isName) {
        /*Instruction* load = new Load((NameInstruction*)address);
        basicBlocks->back()->Add(load);*/
        return address;
    }
    else return address;
}

//ARGS : EXP COMMA ARGS
vector<Instruction*>* ARGS1::Gen(vector<BasicBlock*>* basicBlocks, bool leftValue) {
    vector<Instruction*>* arguments = args->Gen(basicBlocks);
    arguments->push_back(exp->Gen(basicBlocks));
    return arguments;
}

//ARGS : EXP
vector<Instruction*>* ARGS2::Gen(vector<BasicBlock*>* basicBlocks, bool leftValue) {
    vector<Instruction*>* args = new vector<Instruction*>;
    args->push_back(exp->Gen(basicBlocks, leftValue));
    
    return args;
}

//ARGS :
vector<Instruction*>* ARGS3::Gen(vector<BasicBlock*>* basicBlocks, bool leftValue) {
    return new vector<Instruction*>;
}

void PROGRAM::Emit(ofstream& os) {
    module->Emit(os);
}