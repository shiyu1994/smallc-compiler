#include "Instruction.h"
#include "Type.h"
#include <fstream>

/*
 Define how each instruction is emitted into .ll file.
 */

int Instruction::counter = 0;

int Instruction::label = 0;

Instruction::Instruction(Type* type) : type(type), address(""), isName(false), isNum(false), isBranch(false) {}

void Instruction::SetCounterToZero() {
    counter = 0;
}

BinaryOperation::BinaryOperation(const char* bop, Instruction* lop, Instruction* rop, Type* type)
: binaryOp(bop), leftOperand(lop), rightOperand(rop), Instruction(type) {
    live = false;
}

/*
 Resolve labels for basic blocks
 */
void BinaryOperation::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", ++counter);
    address = name;
    address = "%" + address;
}

void BinaryOperation::CheckReferences() {
    live = true;
    leftOperand->CheckReferences();
    rightOperand->CheckReferences();
}

/*
 For binary operation, first emit the operator name, then two operands.
 */
void BinaryOperation::Emit(ofstream& os) {
    os << this->address << " = ";
    string op = binaryOp;
    if(op == "+") {
        os << "add ";
    }
    else if(op == "-") {
        os << "sub ";
    }
    else if(op == "*") {
        os << "mul ";
    }
    else if(op == "/") {
        os << "sdiv";
    }
    else if(op == "%") {
        os << "srem";
    }
    else if(op == "<") {
        os << "icmp slt";
    }
    else if(op == ">") {
        os << "icmp sgt";
    }
    else if(op == "<=") {
        os << "icmp sle";
    }
    else if(op == ">=") {
        os << "icmp sge";
    }
    else if(op == "==") {
        os << "icmp eq";
    }
    else if(op == "!=") {
        os << "icmp ne";
    }
    else if(op == "&" || op == "&&") {
        os << "and";
    }
    else if(op == "^") {
        os << "xor";
    }
    else if(op == "|" || op == "||") {
        os << "or";
    }
    else if(op == ">>") {
        os << "ashr";
    }
    else if (op == "<<") {
        os << "ashl";
    }
    os << " ";
    leftOperand->type->Emit(os);
    os << " " << leftOperand->address << ",";
    os << " ";
    os << rightOperand->address << endl;
}

UnaryOperation::UnaryOperation(const char* uop, Instruction* operand, Type* type)
: unaryOp(uop), operand(operand), Instruction(type) {
    live = false;
}

void UnaryOperation::CheckReferences() {
    live = true;
    operand->CheckReferences();
}

void UnaryOperation::Emit(ofstream& os) {}

void UnaryOperation::PassForBranch() {}

Compare::Compare(Instruction* leftOperand, Instruction* rightOperand) : leftOperand(leftOperand), rightOperand(rightOperand), Instruction(new Int()) {}

void Compare::Emit(ofstream& os) {}

void Compare::CheckReferences() {}

void Compare::PassForBranch() {}

//A branch takes two basic blocks as destination, and one result as flag.
Branch::Branch(Instruction* compareResult, BasicBlock* leftBranch, BasicBlock* rightBranch) : compareResult(compareResult), leftBranch(leftBranch), rightBranch(rightBranch), Instruction(new EmptyType()) {
    leftBranch->referenceCounter++;
    rightBranch->referenceCounter++;
    isBranch = true;
    live = true;
}

void Branch::CheckReferences() {
    live = true;
    compareResult->CheckReferences();
}

/*
 Resolve labels for basic blocks
 */
void Branch::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", counter);
    address = name;
    address = "%" + address;
}

void Branch::Emit(ofstream& os) {
    os << "br i1 " << compareResult->address << ", label %"
    << leftBranch->name << ", label %" << rightBranch->name << endl;
}


UncondBranch::UncondBranch(BasicBlock* destination) : destination(destination), Instruction(new EmptyType()) {
    destination->referenceCounter++;
    isBranch = true;
    live = true;
}

/*
 Resolve labels for basic blocks
 */
void UncondBranch::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", counter);
    address = name;
    address = "%" + address;
}

void UncondBranch::CheckReferences() {
    live = true;
}

void UncondBranch::Emit(ofstream& os) {
    os << "br label %" << destination->name << endl;
}

Store::Store(Instruction* address, Instruction* value) : address(address), value(value), Instruction(new EmptyType()) {
    live = true;
}

//For store, first emit the value to be sotred, then the address
void Store::Emit(ofstream& os) {
    os << "store ";
    value->type->Emit(os);
    os << " ";
    os << value->address;
    os << ", ";
    address->type->Emit(os);
    os << "* ";
    os << address->address << endl;
}

void Store::CheckReferences() {
    live = true;
    address->CheckReferences();
    value->CheckReferences();
}

void Store::PassForBranch() {}

Load::Load(Instruction* address) : address(address), Instruction(address->type) {}

void Load::CheckReferences() {
    live = true;
    address->CheckReferences();
}

/*
 Resolve labels for basic blocks
 */
void Load::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", ++counter);
    Instruction::address = name;
    Instruction::address = "%" + Instruction::address;
}

//For load, emit the address to load from
void Load::Emit(ofstream& os) {
    os << Instruction::address << " = load ";
    address->type->Emit(os);
    os << "* ";
    os << address->address << endl;
}

Alloca::Alloca(Symbol* symbol) : symbol(symbol), Instruction(symbol->type) {
    live = true;
}

Alloca::Alloca(Type* type) : symbol(NULL), Instruction(type) {}

void Alloca::CheckReferences() {
    live = true;
}

/*
 Resolve labels for basic blocks
 */
void Alloca::PassForBranch() {
    if(symbol == NULL) {
        char* name = new char[10];
        sprintf(name, "%d", ++counter);
        Instruction::address = name;
        Instruction::address = "%" + Instruction::address;
    } else {
        address = "%" + symbol->name;
    }
}

/*
 For memory allocation, just emit the type of variable
 */
void Alloca::Emit(ofstream& os) {
    os << address << " = alloca ";
    type->Emit(os);
    os << endl;
}

/*
 We need to tell whether a element is extract from array or from struct
 */
GetElementPtr::GetElementPtr(Instruction* address, Instruction* index, Array* arrayType)
: address(address), index(index), arrayType(arrayType), Instruction(new EmptyType()) {
    if(!index->isNum && arrayType == NULL) {
        int indexInStruct = 0;
        Structure* structType = (Structure*)address->type;
        NameInstruction* nameInstruction = (NameInstruction*)index;
        for(int i = 0; i < structType->elementTypes.size(); ++i) {
            if(structType->elementTypes[i]->name == nameInstruction->symbol->name) {
                type = structType->elementTypes[i]->type;
                indexInStruct = i;
            }
        }
    } else {
        NumInstruction* numInstruction = (NumInstruction*)index;
        if(address->type->isStruct) {
            type = ((Structure*)address->type)->elementTypes[numInstruction->num]->type;
        }
        else {
            type = (arrayType->elementType);
        }
    }
    live = false;
}

void GetElementPtr::CheckReferences() {
    live = true;
    address->CheckReferences();
    index->CheckReferences();
}

/*
 Resolve labels for basic blocks
 */
void GetElementPtr::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", ++counter);
    Instruction::address = name;
    Instruction::address = "%" + Instruction::address;
}

void GetElementPtr::Emit(ofstream& os) {
    os << Instruction::address << " = getelementptr inbounds ";
    if(!index->isNum && arrayType == NULL) {
        int indexInStruct = 0;
        Structure* structType = (Structure*)address->type;
        NameInstruction* nameInstruction = (NameInstruction*)index;
        for(int i = 0; i < structType->elementTypes.size(); ++i) {
            if(structType->elementTypes[i]->name == nameInstruction->symbol->name) {
                indexInStruct = i;
            }
        }
        structType->Emit(os);
        os << "* " << address->address;
        os << ", i32 0, ";
        os << "i32 " << indexInStruct << endl;
    } else {
        address->type->Emit(os);
        os << "* " << address->address;
        os << ", i32 0, ";
        index->type->Emit(os);
        os << " ";
        os << index->address << endl;
    }
}

Return::Return(Instruction* address, Type* type) : address(address), Instruction(type) {
    isBranch = true;
    live = true;
}

void Return::CheckReferences() {
    live = true;
    address->CheckReferences();
}

/*
 Resolve labels for basic blocks
 */
void Return::PassForBranch() {}

void Return::Emit(ofstream& os) {
    os << "ret ";
    address->type->Emit(os);
    os << " ";
    os << address->address << endl;
}

FunctionCall::FunctionCall(Instruction* function, vector<Instruction*>* arguments, Type* type)
: function(function), arguments(arguments), Instruction(type) {
    live = true;
}

void FunctionCall::CheckReferences() {
    live = true;
    function->CheckReferences();
    for(int i = 0; i < arguments->size(); ++i) {
        (*arguments)[i]->CheckReferences();
    }
}

/*
 Resolve labels for basic blocks
 */
void FunctionCall::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", ++counter);
    address = name;
    address = "%" + address;
}

/*
 For function call, first emit the return type and function name, then the arguments.
 */
void FunctionCall::Emit(ofstream& os) {
    if(function->address == "%read") {
        callRead(os);
        return;
    }
    else if(function->address == "%write") {
        callWrite(os);
        return;
    }
    os << address << " = call ";
    type->Emit(os);
    os << " ";
    os << function->address << "(";
    if(arguments->size() > 0) {
        for(int i = 0; i < arguments->size() - 1; ++i) {
            (*arguments)[i]->type->Emit(os);
            os << " ";
            os << (*arguments)[arguments->size() - 1 - i]->address;
            os << ", ";
        }
        arguments->back()->type->Emit(os);
        os << " " << arguments->front()->address;
    }
    os << ")";
    os << endl;
}

//Treat I/O as special cases, use printf and scanf
void FunctionCall::callRead(ofstream& os) {
    os << address << " = call ";
    os << "i32 (i8*, ...)* @scanf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32* ";
    os << (*arguments)[0]->address << ")" << endl;
}

void FunctionCall::callWrite(ofstream& os) {
    os << address << " = call ";
    os << "i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str1, i32 0, i32 0), i32 ";
    os << (*arguments)[0]->address << ")" << endl;
}

//pseudo instruction, just indicate a number value
NumInstruction::NumInstruction(int num) : num(num), Instruction(new Int()) {
    char* name = new char[10];
    sprintf(name, "%d", num);
    Instruction::address = name;
    isNum = true;
    live = false;
}

void NumInstruction::CheckReferences() {
    live = true;
}

void NumInstruction::PassForBranch() {}

void NumInstruction::Emit(ofstream& os) {
    //os << num;
}

//pseudo instruction, just indicate a variable
NameInstruction::NameInstruction(Symbol* symbol) : symbol(symbol), Instruction(symbol->type) {
    address = symbol->name;
    if(symbol->isGlobal) {
        address = "@" + address;
    }
    else {
        address = "%" + address;
    }
    isName = true;
    live = false;
}

void NameInstruction::CheckReferences() {
    live = true;
}

void NameInstruction::PassForBranch() {}

void NameInstruction::Emit(ofstream& os) {}

ZeroExtension::ZeroExtension(Instruction* address) : address(address), Instruction(new Int()) {
    live = false;
}

void ZeroExtension::CheckReferences() {
    live = true;
    address->CheckReferences();
}

/*
 Resolve labels for basic blocks
 */
void ZeroExtension::PassForBranch() {
    char* name = new char[10];
    sprintf(name, "%d", ++counter);
    Instruction::address = name;
    Instruction::address = "%" + Instruction::address;
}

void ZeroExtension::Emit(ofstream& os) {
    os << Instruction::address << " = zext i1 ";
    os << address->address;
    os << " to i32" << endl;
}