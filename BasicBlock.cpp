#include "BasicBlock.h"
#include "Instruction.h"
#include <vector>
#include <string>
#include <fstream>

/*
 This file implements the methods for basic blocks. Including closing a basic block, emitting a basic block to .ll file, deals with the label of basic blocks and optimization.
 */

using namespace std;

//Indicating whether the last emitted basic block ends with a branch or return
bool BasicBlock::lastClosedWithBranch = true;

BasicBlock::BasicBlock(string name) : instructionCounter(0), closed(false), name(name) {
    referenceCounter = 0;
    endWithBranch = false;
}

BasicBlock::BasicBlock(int instructionCounter) : instructionCounter(instructionCounter), closed(false) {
    referenceCounter = 0;
    endWithBranch = false;
}

//Add an instruction to a basic block
void BasicBlock::Add(Instruction *instruction) {
    instructions.push_back(instruction);
}

//Make the basic block close, no more instruction can be generated into this basic block
void BasicBlock::Close() {
    closed = true;
}

bool BasicBlock::IsClosed() {
    return closed;
}

//Get the last instruction of a basic block
Instruction* BasicBlock::LastInstruction() {
    return instructions.back();
}

//Emit intermediate code of a basic block to .ll file
void BasicBlock::Emit(ofstream& os) {
    if((instructions.size() > 0 && referenceCounter > 0) || name == "entry") {
        if(!lastClosedWithBranch) {
            UncondBranch* branch = new UncondBranch(this);
            branch->Emit(os);
        }
        if(name != "entry")
            os << name + ":" << endl;
        for(int i = 0; i < instructions.size(); ++i) {
            instructions[i]->Emit(os);
        }
        lastClosedWithBranch = instructions.back()->isBranch;
    }
}

int BasicBlock::Length() {
    return (int)instructions.size();
}

//Resolve the label for basicblocks
void BasicBlock::PassForBranch() {
    if((instructions.size() > 0 && referenceCounter > 0) || name == "entry") {
        if(name != "entry") {
            char* myname = new char[10];
            sprintf(myname, "L%d", ++Instruction::label);
            name = myname;
        }
        for(int i = 0; i < instructions.size(); ++i) {
            instructions[i]->PassForBranch();
        }
    }
}

//Indicating whether this basic block is reachable
bool BasicBlock::isLive() {
    return instructions.size() > 0 && referenceCounter > 0;
}

//Search and mark the useful instructions
void BasicBlock::Optimize() {
    for(int i = 0; i < instructions.size(); ++i) {
        if(instructions[i]->live)
            instructions[i]->CheckReferences();
    }
}

//Delete useless instructions
void BasicBlock::Clean() {
    vector<Instruction*>* useful = new vector<Instruction*>;
    for(int i = 0; i < instructions.size(); ++i) {
        if(instructions[i]->live) {
            useful->push_back(instructions[i]);
        }
    }
    instructions = *useful;
}