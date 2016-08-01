#ifndef INSTRUCTION_INCLUDED_H
#define INSTRUCTION_INCLUDED_H

#include "Type.h"
#include "Symbol.h"
#include "BasicBlock.h"
#include "ParseTree.h"
#include <string>
#include <vector>
#include <fstream>

/*
 Define data structures for instructions
 */

using namespace std;

class BasicBlock;
class OP;
enum BINARYOP {
ADD, SUB, MUL, DIV
};

enum UNARYOP {NEG};

class Instruction {
public:
    static int counter;
    int instructionID;
    string address;
    Type* type;
    bool isName;
    bool isNum;
    Instruction(Type* type);
    static void SetCounterToZero();
    virtual void Emit(ofstream& os) = 0;
    virtual void PassForBranch() = 0;
    static int label;
    bool isBranch;
    virtual void CheckReferences() = 0;
    bool live;
};

/*
 Binary operation, has a opeartor and two operands
 */
class BinaryOperation : public Instruction {
private:
    const char* binaryOp;
    Instruction* leftOperand;
    Instruction* rightOperand;
public:
    BinaryOperation(const char* bop, Instruction* lop, Instruction* rop, Type* type);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

/*
 Unary operation, has a operator and one operand
 */
class UnaryOperation : public Instruction {
private:
    const char* unaryOp;
    Instruction* operand;
public:
    UnaryOperation(const char* uop, Instruction* operand, Type* type);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

class Compare : public Instruction {
private:
    Instruction* leftOperand;
    Instruction* rightOperand;
public:
    Compare(Instruction* leftOperand, Instruction* rightOperand);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

// Conditional branch, takes two basicblocks as destination and one instruction result as flag
class Branch : public Instruction {
private:
    Instruction* compareResult;
    BasicBlock* leftBranch;
    BasicBlock* rightBranch;
public:
    Branch(Instruction* compareResult, BasicBlock* leftBranch, BasicBlock* rightBranch);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//Unconditional branch, take one basic block as destination
class UncondBranch : public Instruction {
private:
    BasicBlock* destination;
public:
    UncondBranch(BasicBlock* destination);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//Store, take one instrution result as address and another as value to be stored
class Store : public Instruction {
private:
    Instruction* address;
    Instruction* value;
public:
    Store(Instruction* address, Instruction* value);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

class NameInstruction;
//Load, take one instruction result, typically a name instruction as address
class Load : public Instruction {
private:
    Instruction* address;
public:
    Load(Instruction* address);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//Allocation, it needs the symbol of variable which requires memory allocation.
class Alloca : public Instruction {
private:
    Symbol* symbol;
public:
    Alloca(Symbol* symbol);
    Alloca(Type* type);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//Get element from array or struct, it takes an address and and index.
class GetElementPtr : public Instruction {
private:
    Instruction* address;
    Instruction* index;
    Array* arrayType;
public:
    GetElementPtr(Instruction* address, Instruction* index, Array* arrayType = NULL);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//Return instruction, it takes a instruction result as return value
class Return : public Instruction {
private:
    Instruction* address;
public:
    Return(Instruction* address, Type* type);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//Function call, it needs a name instruction indicating the function name.
class FunctionCall : public Instruction {
private:
    void callRead(ofstream& os);
    void callWrite(ofstream& os);
public:
    Instruction* function;
    vector<Instruction*>* arguments;
    FunctionCall(Instruction* function, vector<Instruction*>* arguments, Type* type);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//pseudo instruction, only indicates a number value
class NumInstruction : public Instruction {
public:
    int num;
    NumInstruction(int num);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

//pseudo instruction, only indicates an identifier
class NameInstruction : public Instruction {
public:
    Symbol* symbol;
    NameInstruction(Symbol* symbol);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};

class EmptyInstruction : public Instruction {
public:
    EmptyInstruction() : Instruction(NULL) {}
    void PassForBranch();
    void CheckReferences();
};

//Zero extension, needs the instruction result for the value to do zero extension.
class ZeroExtension : public Instruction {
private:
    Instruction* address;
public:
    ZeroExtension(Instruction* address);
    void Emit(ofstream& os);
    void PassForBranch();
    void CheckReferences();
};
#endif