#ifndef BASIC_BLOCK_H_INCLUDED
#define BASIC_BLOCK_H_INCLUDED

#include <vector>
#include "Instruction.h"
#include <string>
#include <fstream>

/*
 Defines the structure of basic blocks
 */

using namespace std;

class Instruction;
class BasicBlock {
private:
    std::vector<Instruction*> instructions;
    bool closed;
    static bool lastClosedWithBranch;
public:
    int referenceCounter;//How many instructions can branch to this basic block
    int instructionCounter;//Number of instructions in this basic block
    string name;
    BasicBlock(string name = "");
    BasicBlock(int instructionCounter);
    void Add(Instruction* instruction);
    std::vector<BasicBlock*> trueSuccessor;//deprecated
    std::vector<BasicBlock*> falseSuccessor;//deprecated
    void Close();
    bool IsClosed();
    Instruction* LastInstruction();
    void Emit(ofstream &os);
    int Length();
    void PassForBranch();
    bool endWithBranch;
    bool isLive();
    void Optimize();
    void Clean();
};

#endif