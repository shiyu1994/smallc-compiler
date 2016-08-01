#ifndef PARSETREE_H
#define PARSETREE_H

extern "C" {
#include "common.h"
}
#include <cstring>
#include <iostream>
#include <vector>
#include "SymbolTable.h"
#include "Symbol.h"
#include "Type.h"
#include "Instruction.h"
#include "Module.h"
#include "BasicBlock.h"
#include <fstream>

/*
 Define classes for nonterminals, identifiers and productions, the corresponding grammar structure is commented right above each definition
 */

using namespace std;

class Instruction;
class Module;
class BasicBlock;

class ParseTree {
protected:
    static SymbolTable* symbolTable;
    static TupleType* EMPTY_TYPE;
    static Module* module;
public:
    static char* getContent(const char *nodeName);
    int lineNumber;
};

class EXTDEFS;
//PROGRAM : EXTDEFS
class PROGRAM : public ParseTree {
private:
    EXTDEFS* extdefs;
public:
    PROGRAM(tree* rawTree);
    void Typer();
    void Gen();
    void Emit(ofstream& os);
    void Optimize();
};

class EXTDEFS : public ParseTree {
public:
    static EXTDEFS* createEXTDEFS(tree* rawTree);
    virtual void Typer() = 0;
    virtual void Gen() = 0;
};

//EXTDEFS : EXTDEF EXTDEFS
class EXTDEF;
class EXTDEFS1 : public EXTDEFS {
private:
    EXTDEF* extdef;
    EXTDEFS* extdefs;
public:
    EXTDEFS1(tree* rawTree);
    void Typer();
    void Gen();
};

//EXTDEFS :
class EXTDEFS2 : public EXTDEFS {
public:
    EXTDEFS2(tree* rawTree);
    void Typer();
    void Gen();
};


class EXTDEF : public ParseTree {
public:
    static EXTDEF* createEXTDEF(tree* rawTree);
    virtual void Typer() = 0;
    virtual void Gen() = 0;
};

//EXTDEF : SPEC EXTVARS SEMI
class SPEC;
class EXTVARS;
class EXTDEF1 : public EXTDEF {
private:
    SPEC* spec;
    EXTVARS* extvars;
public:
    EXTDEF1(tree* rawTree);
    void Typer();
    void Gen();
};

//EXTDEF : SPEC FUNC STMTBLOCK
class FUNC;
class STMTBLOCK;
class EXTDEF2 : public EXTDEF {
private:
    SPEC* spec;
    FUNC* func;
    STMTBLOCK* stmtblock;
public:
    EXTDEF2(tree* rawTree);
    void Typer();
    void Gen();
};

class EXTVARS : public ParseTree {
public:
    static EXTVARS* createEXTVARS(tree* rawTree);
    virtual void Typer(Type* type = EMPTY_TYPE) = 0;
    virtual void SetFieldSymbols(SymbolTableFrame* fieldSymbol) = 0;
    virtual void Gen() = 0;
};

//EXTVARS : DEC
class DEC;
class EXTVARS1 : public EXTVARS {
private:
    DEC* dec;
public:
    EXTVARS1(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};

//EXTVARS : DEC COMMA EXTVARS
class EXTVARS2 : public EXTVARS {
private:
    DEC* dec;
    EXTVARS* extvars;
public:
    EXTVARS2(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};

//EXTVARS :
class EXTVARS3 : public EXTVARS {
public:
    EXTVARS3(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};

class SPEC : public ParseTree {
    friend class PARA;
    friend class DEF;
    friend class EXTDEF1;
    friend class EXTDEF2;
protected:
    Type* specType;
public:
    static SPEC* createSPEC(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual SymbolTableFrame* GetFieldSymbols() = 0;
    virtual void Gen() = 0;
};

//SPEC : TYPE
class TYPE;
class SPEC1 : public SPEC {
private:
    TYPE* type;
public:
    SPEC1(tree* rawTree);
    Type* Typer();
    void Gen();
    SymbolTableFrame* GetFieldSymbols();
};

//SPEC : STSPEC
class STSPEC;
class SPEC2 : public SPEC {
private:
    STSPEC* stspec;
public:
    SPEC2(tree* rawTree);
    Type* Typer();
    void Gen();
    SymbolTableFrame* GetFieldSymbols();
};

class STSPEC : public ParseTree {
    friend class SPEC2;
public:
    static STSPEC* createSTSPEC(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual SymbolTableFrame* GetFieldSymbols() = 0;
    virtual void Gen() = 0;
};

//STSPEC : STRUCT OPTTAG LC DEFS RC
class OPTTAG;
class DEFS;
class STSPEC1 : public STSPEC {
private:
    OPTTAG* opttag;
    DEFS* defs;
public:
    STSPEC1(tree* rawTree);
    Type* Typer();
    void Gen();
    SymbolTableFrame* GetFieldSymbols();
};

//STSPEC : STRUCT ID
class ID;
class STSPEC2 : public STSPEC {
private:
    ID* name;
public:
    STSPEC2(tree* rawTree);
    Type* Typer();
    void Gen();
    SymbolTableFrame* GetFieldSymbols();
};

class OPTTAG : public ParseTree {
public:
    static OPTTAG* createOPPTAG(tree* rawTree);
    static int anonId;
    virtual void Typer(Type* type = EMPTY_TYPE) = 0;
    virtual void SetFieldSymbols(SymbolTableFrame* fieldSymbols) = 0;
    virtual SymbolTableFrame* GetFieldSymbols() = 0;
    virtual void Gen() = 0;
    virtual Symbol* GetSymbol() = 0;
    
};

//OPTTAG : ID
class STSPEC1;
class OPTTAG1 : public OPTTAG {
private:
    ID* name;
public:
    OPTTAG1(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbols);
    SymbolTableFrame* GetFieldSymbols();
    Symbol* GetSymbol();
};

//OPTTAG :
class OPTTAG2 : public OPTTAG {
private:
    Symbol* symbol;
public:
    OPTTAG2(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbols);
    SymbolTableFrame* GetFieldSymbols();
    Symbol* GetSymbol();
};

class VAR : public ParseTree {
public:
    static VAR* createVAR(tree* rawTree, int dimension);
    static void GenInits(Type* varType, Instruction* address, std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks, int& counter);
    virtual Type* Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL) = 0;
    virtual void SetFieldSymbols(SymbolTableFrame* fieldSymbol) = 0;
    virtual void Gen(std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks  = NULL) = 0;
    virtual void Gen() = 0;
    virtual string GetName() = 0;
    virtual Symbol* GetSymbol() = 0;
};

//VAR : ID
class VAR1 : public VAR {
private:
    ID* name;
public:
    VAR1(tree* rawTree, int dimension);
    Type* Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL);
    void Gen(std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks  = NULL);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
    string GetName();
    Symbol* GetSymbol();
};

//VAR : VAR LB INT RB
class NUM;
class VAR2 : public VAR {
private:
    VAR* var;
    NUM* num;
public:
    VAR2(tree* rawTree, int dimension);
    Type* Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL);
    void Gen(std::vector<Instruction*>* initValues, std::vector<BasicBlock*>* basicBlocks  = NULL);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
    string GetName();
    Symbol* GetSymbol();
};

//FUNC : ID LP PARAS RP
class PARAS;
class FUNC : public ParseTree {
private:
    PARAS* paras;
public:
    ID* name;
    FUNC(tree* rawTree);
    Type* Typer(Type* type);
    void Gen();
    void SetFieldSymbols(SymbolTableFrame* fieldSymbols);
    SymbolTableFrame* GetFieldSymbols();
    Symbol* GetSymbol();
    vector<Symbol*>* CollectParaSymbols();
};

class PARAS : public ParseTree {
public:
    static PARAS* createPARAS(tree* rawTree);
    virtual Structure* Typer() = 0;
    virtual void Gen() = 0;
    virtual vector<Symbol*>* CollectParaSymbols() = 0;
};

//PARAS : PARA COMMA PARAS
class PARA;
class PARAS1 : public PARAS {
private:
    PARA* para;
    PARAS* paras;
public:
    PARAS1(tree* rawTree);
    Structure* Typer();
    void Gen();
    vector<Symbol*>* CollectParaSymbols();
};

//PARAS : PARA
class PARAS2 : public PARAS {
private:
    PARA* para;
public:
    PARAS2(tree* rawTree);
    Structure* Typer();
    void Gen();
    vector<Symbol*>* CollectParaSymbols();
};

//PARAS :
class PARAS3 : public PARAS {
public:
    PARAS3(tree* rawTree);
    Structure* Typer();
    void Gen();
    vector<Symbol*>* CollectParaSymbols();
};

//PARA : SPEC VAR
class PARA : public ParseTree {
private:
    SPEC* spec;
    VAR* var;
public:
    PARA(tree* rawTree);
    Type* Typer();
    void Gen();
    string GetName();
    Symbol* GetSymbol();
};

//STMTBLOCK LC DEFS STMTS RC
class STMTS;
class STMTBLOCK : public ParseTree {
private:
    DEFS* defs;
    STMTS* stmts;
public:
    STMTBLOCK(tree* rawTree);
    Type* Typer();
    void GenBasicBlocks(std::vector<BasicBlock*>* basicBlocks,
                        BasicBlock* next = NULL,
                        BasicBlock* cont = NULL,
                        BasicBlock* breakTo = NULL);
};

class STMTS : public ParseTree {
public:
    static STMTS* createSTMTS(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks,
                     BasicBlock* next = NULL,
                     BasicBlock* cont = NULL,
                     BasicBlock* breakTo = NULL) = 0;
};

//STMTS : STMT STMTS
class STMT;
class STMTS1 : public STMTS {
private:
    STMT* stmt;
    STMTS* stmts;
public:
    STMTS1(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMTS :
class STMTS2 : public STMTS {
public:
    STMTS2(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

class STMT : public ParseTree {
public:
    static STMT* createSTMT(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks,
                     BasicBlock* next = NULL,
                     BasicBlock* cont = NULL,
                     BasicBlock* breakTo = NULL) = 0;
};

//STMT : EXP SEMI
class EXP;
class STMT1 : public STMT {
private:
    EXP* exp;
public:
    STMT1(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMT : STMTBLOCK
class STMT2 : public STMT {
private:
    STMTBLOCK* stmtblock;
public:
    STMT2(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMT : RETURN EXP SEMI
class STMT3 : public STMT {
private:
    EXP* exp;
public:
    STMT3(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMT : IF LP EXP RP STMT ESTMT
class ESTMT;
class STMT4 : public STMT {
private:
    EXP* exp;
    STMT* stmt;
    ESTMT* estmt;
public:
    STMT4(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMT : FOR LP FOREXP SEMI FOREXP SEMI FOREXP RP STMT
class FOREXP;
class STMT5 : public STMT {
private:
    FOREXP *forexp1, *forexp2, *forexp3;
    STMT* stmt;
public:
    STMT5(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMT : CONT SEMI
class STMT6 : public STMT {
public:
    STMT6(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//STMT : BREAK SEMI
class STMT7 : public STMT {
public:
    STMT7(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

class ESTMT : public ParseTree {
public:
    bool isEmpty;
    static ESTMT* createESTMT(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks,
                     BasicBlock* next = NULL,
                     BasicBlock* cont = NULL,
                     BasicBlock* breakTo = NULL) = 0;
};

//ESTMT : ELSE STMT
class ESTMT1 : public ESTMT {
private:
    STMT* stmt;
public:
    ESTMT1(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

//ESTMT :
class ESTMT2 : public ESTMT {
public:
    ESTMT2(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* next = NULL,
             BasicBlock* cont = NULL,
             BasicBlock* breakTo = NULL);
};

class DEFS : public ParseTree {
public:
    static DEFS* createDEFS(tree* rawTree);
    virtual void Typer(Type* type = EMPTY_TYPE) = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks  = NULL) = 0;
};

//DEFS : DEF DEFS
class DEF;
class DEFS1 : public DEFS {
private:
    DEF* def;
    DEFS* defs;
public:
    DEFS1(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen(std::vector<BasicBlock*>* basicBlocks  = NULL);
};

//DEFS :
class DEFS2 : public DEFS {
public:
    DEFS2(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen(std::vector<BasicBlock*>* basicBlocks  = NULL);
};

//DEF : SPEC DECS SEMI
class DECS;
class DEF : public ParseTree {
private:
    SPEC* spec;
    DECS* decs;
public:
    DEF(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE);
    void Gen(std::vector<BasicBlock*>* basicBlocks  = NULL);
};

class DECS : public ParseTree {
public:
    static DECS* createDECS(tree* rawTree);
    virtual void Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL) = 0;
    virtual void SetFieldSymbols(SymbolTableFrame* fieldSymbol) = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks) = 0;
};

//DECS : DEC COMMA DECS
class DECS1 : public DECS {
private:
    DEC* dec;
    DECS* decs;
public:
    DECS1(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL);
    void Gen(std::vector<BasicBlock*>* basicBlocks);
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};

//DECS : DEC
class DECS2 : public DECS {
private:
    DEC* dec;
public:
    DECS2(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL);
    void Gen(std::vector<BasicBlock*>* basicBlocks);
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};

class DEC : public ParseTree {
public:
    static DEC* createDEC(tree* rawTree);
    virtual void Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL) = 0;
    virtual void SetFieldSymbols(SymbolTableFrame* fieldSymbol) = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks = NULL) = 0;
};

//DEC : VAR
class DEC1 : public DEC {
private:
    VAR* var;
public:
    DEC1(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL);
    void Gen(std::vector<BasicBlock*>* basicBlocks = NULL);
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};


//DEC : VAR ASSIGNOP INIT
class INIT;
class DEC2 : public DEC {
private:
    VAR* var;
    INIT* init;
public:
    DEC2(tree* rawTree);
    void Typer(Type* type = EMPTY_TYPE, Structure* structureType = NULL);
    void Gen(std::vector<BasicBlock*>* basicBlocks = NULL);
    void SetFieldSymbols(SymbolTableFrame* fieldSymbol);
};

class INIT : public ParseTree {
public:
    static INIT* createINIT(tree* rawTree);
    virtual Structure* Typer() = 0;
    virtual vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks = NULL) = 0;
};

//INIT : EXP
class INIT1: public INIT {
private:
    EXP* exp;
public:
    INIT1(tree* rawTree);
    Structure* Typer();
    vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks = NULL);
};

//INIT LC ARGS RC
class ARGS;
class INIT2 : public INIT {
private:
    ARGS* args;
public:
    INIT2(tree* rawTree);
    Structure* Typer();
    vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks = NULL);
};

class FOREXP : public ParseTree {
public:
    static FOREXP* createFOREXP(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual void Gen(std::vector<BasicBlock*>* basicBlocks,
                     BasicBlock* trueList = NULL,
                     BasicBlock* falseList = NULL) = 0;
};

//FOREXP : EXP
class FOREXP1 : public FOREXP {
private:
    EXP* exp;
public:
    FOREXP1(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
};

//FOREXP :
class FOREXP2 : public FOREXP {
public:
    FOREXP2(tree* rawTree);
    Type* Typer();
    void Gen(std::vector<BasicBlock*>* basicBlocks,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
};

class EXP : public ParseTree {
public:
    static EXP* createEXP(tree* rawTree);
    virtual Type* Typer() = 0;
    virtual SymbolTableFrame* GetFieldSymbols() = 0;
    virtual Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
                     BasicBlock* trueList = NULL,
                     BasicBlock* falseList = NULL) = 0;
    virtual string GetIDName() = 0;
};

//EXP : EXP BINARYOP EXP
class OP;
class EXP1 : public EXP {
private:
    EXP *exp1, *exp2;
    OP* op;
public:
    EXP1(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : UNARYOP EXP
class EXP2 : public EXP {
private:
    OP* op;
    EXP* exp;
public:
    EXP2(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : '-' EXP
class EXP3 : public EXP {
private:
    EXP* exp;
public:
    EXP3(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : LP EXP RP
class EXP4 : public EXP {
private:
    EXP* exp;
public:
    EXP4(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : ID LP ARGS RP
class ID;
class EXP5 : public EXP {
private:
    ID* name;
    ARGS* args;
public:
    EXP5(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : ID ARRS
class ARRS;
class EXP6 : public EXP {
private:
    ID* name;
    ARRS* arrs;
public:
    EXP6(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : EXP DOT ID
class EXP7 : public EXP {
private:
    EXP* exp;
    ID* name;
public:
    EXP7(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : INT
class EXP8 : public EXP {
private:
    NUM* num;
public:
    EXP8(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP : ID ARRS ASSIGNOP EXP
class EXP9 : public EXP {
private:
    ID* name;
    ARRS* arrs;
    EXP* exp;
    char* op;
public:
    EXP9(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

//EXP DOT ID ASSIGNOP EXP
class EXP10 : public EXP {
private:
    EXP* exp1;
    ID* name;
    EXP* exp2;
    char* op;
public:
    EXP10(tree* rawTree);
    Type* Typer();
    Instruction* Gen(std::vector<BasicBlock*>* basicBlocks, bool leftVal = false,
             BasicBlock* trueList = NULL,
             BasicBlock* falseList = NULL);
    SymbolTableFrame* GetFieldSymbols();
    string GetIDName();
};

class ARRS : public ParseTree {
public:
    static ARRS* createARRS(tree* rawTree);
    virtual Type* Typer(Type* type = EMPTY_TYPE) = 0;
    virtual int Dimension() = 0;
    virtual Instruction* Gen(Instruction* address, Type* arrayType, vector<BasicBlock*>* basicBlocks) = 0;
    virtual bool isEmpty() = 0;
};

//ARRS : LB EXP RB ARRS
class ARRS1 : public ARRS {
private:
    EXP* exp;
    ARRS* arrs;
public:
    ARRS1(tree* rawTree);
    Type* Typer(Type* type = EMPTY_TYPE);
    Instruction* Gen(Instruction* address, Type* arrayType, vector<BasicBlock*>* basicBlocks);
    int Dimension();
    bool isEmpty();
};

//ARRS :
class ARRS2 : public ARRS {
public:
    ARRS2(tree* rawTree);
    Type* Typer(Type* type = EMPTY_TYPE);
    Instruction* Gen(Instruction* address, Type* arrayType, vector<BasicBlock*>* basicBlocks);
    int Dimension();
    bool isEmpty();
};


class ARGS : public ParseTree {
public:
    static ARGS* createARGS(tree* rawTree);
    virtual Structure* Typer() = 0;
    virtual vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks, bool leftValue = false) = 0;
};

//ARGS : EXP COMMA ARGS
class ARGS1 : public ARGS {
private:
    EXP* exp;
    ARGS* args;
public:
    ARGS1(tree* rawTree);
    Structure* Typer();
    vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks, bool leftValue = false);
};

//ARGS : EXP
class ARGS2 : public ARGS {
private:
    EXP* exp;
public:
    ARGS2(tree* rawTree);
    Structure* Typer();
    vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks, bool leftValue = false);
};

//ARGS :
class ARGS3 : public ARGS {
public:
    ARGS3(tree* rawTree);
    Structure* Typer();
    vector<Instruction*>* Gen(vector<BasicBlock*>* basicBlocks, bool leftValue = false);
};

class EMPTY : public ParseTree {
public:
    void Type() {};
    void Gen() {};
};

class ID : public ParseTree {
private:
    SymbolTableFrame* fieldSymbols;
    int dimension;
public:
    Symbol* symbol;
    ID(tree* rawTree, bool isFunction, bool isType, int dimension);
    ID(tree* rawTree, int dimension);
    ID(tree* rawTree, SymbolTableFrame* fieldSymbols, int dimension);
    Type* Typer(Type* type = EMPTY_TYPE);
    void Gen() {};
    void SetFieldSymbols(SymbolTableFrame* fieldSymbols);
    SymbolTableFrame* GetFieldSymbols();
};

class NUM : public ParseTree {
public:
    int num;
    NUM(tree* rawTree);
    Type* Typer();
    void Gen() {};
};

class TYPE : public ParseTree {
private:
    char* type;
public:
    TYPE(tree* rawTree);
    Type* Typer();
    void Gen() {};
};

class OP : public ParseTree {
public:
    char* op;
    OP(tree* rawTree);
    void Gen() {};
};


#endif