#include "ParseTree.h"
#include "Type.h"

using namespace std;

/*
 Define constructors that attach symbols to parse tree, each production has such a constructor, and the corresponding production is commented right above the constructors
 */

class Type;

SymbolTable* ParseTree::symbolTable = new SymbolTable();

int OPTTAG::anonId = 0;

EXTDEFS* EXTDEFS::createEXTDEFS(tree *rawTree) {
    EXTDEFS* extdefs;
    if(rawTree->productionId == 1) {
        extdefs = new EXTDEFS1(rawTree);
    }
    else {
        extdefs = new EXTDEFS2(rawTree);
    }
    
    return extdefs;
}

EXTDEF* EXTDEF::createEXTDEF(tree *rawTree) {
    EXTDEF* extdef;
    if(rawTree->productionId == 1) {
        extdef = new EXTDEF1(rawTree);
    }
    else if(rawTree->productionId == 2) {
        extdef = new EXTDEF2(rawTree);
    }
    
    return extdef;
}

EXTVARS* EXTVARS::createEXTVARS(tree *rawTree) {
    EXTVARS* extvars;
    if(rawTree->productionId == 1) {
        extvars = new EXTVARS1(rawTree);
    }
    else if(rawTree->productionId == 2) {
        extvars = new EXTVARS2(rawTree);
    }
    else {
        extvars = new EXTVARS3(rawTree);
    }
    
    return extvars;
}

SPEC* SPEC::createSPEC(tree *rawTree) {
    SPEC* spec;
    if(rawTree->productionId == 1) {
        spec = new SPEC1(rawTree);
    }
    else {
        spec = new SPEC2(rawTree);
    }
    
    return spec;
}

STSPEC* STSPEC::createSTSPEC(tree *rawTree) {
    STSPEC* stspec;
    if(rawTree->productionId == 1) {
        stspec = new STSPEC1(rawTree);
    }
    else {
        stspec = new STSPEC2(rawTree);
    }
    
    return stspec;
}

OPTTAG* OPTTAG::createOPPTAG(tree *rawTree) {
    OPTTAG* opttag;
    if(rawTree->productionId == 1) {
        opttag = new OPTTAG1(rawTree);
    }
    else {
        opttag = new OPTTAG2(rawTree);
    }
    
    return opttag;
}

VAR* VAR::createVAR(tree *rawTree, int dimension) {
    VAR* var;
    if(rawTree->productionId == 1) {
        var = new VAR1(rawTree, dimension);
    }
    else {
        var = new VAR2(rawTree, dimension);
    }
    
    return var;
}

PARAS* PARAS::createPARAS(tree *rawTree) {
    PARAS* paras;
    if(rawTree->productionId == 1) {
        paras = new PARAS1(rawTree);
    }
    else if(rawTree->productionId == 2) {
        paras = new PARAS2(rawTree);
    }
    else {
        paras = new PARAS3(rawTree);
    }
    
    return paras;
}

STMTS* STMTS::createSTMTS(tree *rawTree) {
    STMTS* stmts;
    if(rawTree->productionId == 1) {
        stmts = new STMTS1(rawTree);
    }
    else {
        stmts = new STMTS2(rawTree);
    }
    
    return stmts;
}

STMT* STMT::createSTMT(tree *rawTree) {
    STMT* stmt;
    if(rawTree->productionId == 1) {
        stmt = new STMT1(rawTree);
    }
    else if(rawTree->productionId == 2) {
        stmt = new STMT2(rawTree);
    }
    else if(rawTree->productionId == 3) {
        stmt = new STMT3(rawTree);
    }
    else if(rawTree->productionId == 4) {
        stmt = new STMT4(rawTree);
    }
    else if(rawTree->productionId == 5) {
        stmt = new STMT5(rawTree);
    }
    else if(rawTree->productionId == 6) {
        stmt = new STMT6(rawTree);
    }
    else if(rawTree->productionId == 6) {
        stmt = new STMT6(rawTree);
    }
    else {
        stmt = new STMT7(rawTree);
    }
    
    return stmt;
}

ESTMT* ESTMT::createESTMT(tree *rawTree) {
    ESTMT* estmt;
    if(rawTree->productionId == 1) {
        estmt = new ESTMT1(rawTree);
    }
    else {
        estmt = new ESTMT2(rawTree);
    }
    
    return estmt;
}

DEFS* DEFS::createDEFS(tree *rawTree) {
    DEFS* defs;
    if(rawTree->productionId == 1) {
        defs = new DEFS1(rawTree);
    }
    else {
        defs = new DEFS2(rawTree);
    }
    
    return defs;
}

DECS* DECS::createDECS(tree *rawTree) {
    DECS* decs;
    if(rawTree->productionId == 1) {
        decs = new DECS1(rawTree);
    }
    else {
        decs = new DECS2(rawTree);
    }
    
    return decs;
}

DEC* DEC::createDEC(tree *rawTree) {
    DEC* dec;
    if(rawTree->productionId == 1) {
        dec = new DEC1(rawTree);
    }
    else {
        dec = new DEC2(rawTree);
    }
    
    return dec;
}

INIT* INIT::createINIT(tree *rawTree) {
    INIT* init;
    if(rawTree->productionId == 1) {
        init = new INIT1(rawTree);
    }
    else {
        init = new INIT2(rawTree);
    }
    
    return init;
}

FOREXP* FOREXP::createFOREXP(tree *rawTree) {
    FOREXP* forexp;
    if(rawTree->productionId == 1) {
        forexp = new FOREXP1(rawTree);
    }
    else {
        forexp = new FOREXP2(rawTree);
    }
    
    return forexp;
}

EXP* EXP::createEXP(tree *rawTree) {
    EXP* exp;
    if(rawTree->productionId == 1) {
        exp = new EXP1(rawTree);
    }
    else if(rawTree->productionId == 2) {
        exp = new EXP2(rawTree);
    }
    else if(rawTree->productionId == 3) {
        exp = new EXP3(rawTree);
    }
    else if(rawTree->productionId == 4) {
        exp = new EXP4(rawTree);
    }
    else if(rawTree->productionId == 5) {
        exp = new EXP5(rawTree);
    }
    else if(rawTree->productionId == 6) {
        exp = new EXP6(rawTree);
    }
    else if(rawTree->productionId == 7) {
        exp = new EXP7(rawTree);
    }
    else if(rawTree->productionId == 8) {
        exp = new EXP8(rawTree);
    }
    else if(rawTree->productionId == 9) {
        exp = new EXP9(rawTree);
    }
    else {
        exp = new EXP10(rawTree);
    }
    
    return exp;
}

ARRS* ARRS::createARRS(tree *rawTree) {
    ARRS* arrs;
    if(rawTree->productionId == 1) {
        arrs = new ARRS1(rawTree);
    }
    else {
        arrs = new ARRS2(rawTree);
    }
    
    return arrs;
}

ARGS* ARGS::createARGS(tree *rawTree) {
    ARGS* args;
    if(rawTree->productionId == 1) {
        args = new ARGS1(rawTree);
    }
    else if(rawTree->productionId == 2) {
        args = new ARGS2(rawTree);
    }
    else {
        args = new ARGS3(rawTree);
    }
    
    return args;
}

//PROGRAM : EXTDEFS
PROGRAM::PROGRAM(tree* rawTree) {
    extdefs = EXTDEFS::createEXTDEFS(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//EXTDEFS : EXTDEF EXTDEFS
EXTDEFS1::EXTDEFS1(tree* rawTree) {
    extdef = EXTDEF::createEXTDEF(rawTree->subTrees[0]);
    extdefs = EXTDEFS::createEXTDEFS(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

//EXTDEFS :
EXTDEFS2::EXTDEFS2(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

//EXTDEF : SPEC EXTVARS SEMI
EXTDEF1::EXTDEF1(tree* rawTree) {
    spec = SPEC::createSPEC(rawTree->subTrees[0]);
    extvars = EXTVARS::createEXTVARS(rawTree->subTrees[1]);
    extvars->SetFieldSymbols(spec->GetFieldSymbols());
    lineNumber = rawTree->lineNumber;
}

//EXTDEF : SPEC FUNC STMTBLOCK
EXTDEF2::EXTDEF2(tree* rawTree) {
    spec = SPEC::createSPEC(rawTree->subTrees[0]);
    func = new FUNC(rawTree->subTrees[1]);
    func->SetFieldSymbols(spec->GetFieldSymbols());
    stmtblock = new STMTBLOCK(rawTree->subTrees[2]);
    symbolTable->ExitScope();
    lineNumber = rawTree->lineNumber;
}

//EXTVARS : DEC
EXTVARS1::EXTVARS1(tree* rawTree) {
    dec = DEC::createDEC(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

void EXTVARS1::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    dec->SetFieldSymbols(fieldSymbol);
}

//EXTVARS : DEC COMMA EXTVARS
EXTVARS2::EXTVARS2(tree* rawTree) {
    dec = DEC::createDEC(rawTree->subTrees[0]);
    extvars = EXTVARS::createEXTVARS(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

void EXTVARS2::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    dec->SetFieldSymbols(fieldSymbol);
    extvars->SetFieldSymbols(fieldSymbol);
}

//EXTVARS :
EXTVARS3::EXTVARS3(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

void EXTVARS3::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {}

//SPEC : TYPE
SPEC1::SPEC1(tree* rawTree) {
    type = new TYPE(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

SymbolTableFrame* SPEC1::GetFieldSymbols() {
    return NULL;
}

//SPEC : STSPEC
SPEC2::SPEC2(tree* rawTree) {
    stspec = STSPEC::createSTSPEC(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

SymbolTableFrame* SPEC2::GetFieldSymbols() {
    return stspec->GetFieldSymbols();
}

//STSPEC : STRUCT OPTTAG LC DEFS RC
STSPEC1::STSPEC1(tree* rawTree) {
    opttag = OPTTAG::createOPPTAG(rawTree->subTrees[1]);
    symbolTable->EnterScope();
    defs = DEFS::createDEFS(rawTree->subTrees[3]);
    opttag->SetFieldSymbols(symbolTable->GetCurrFrame());
    symbolTable->ExitScope();
    lineNumber = rawTree->lineNumber;
}

SymbolTableFrame* STSPEC1::GetFieldSymbols() {
    return opttag->GetFieldSymbols();
}

//STSPEC : STRUCT ID
STSPEC2::STSPEC2(tree* rawTree) {
    name = new ID(rawTree->subTrees[1], 0);
    lineNumber = rawTree->lineNumber;
}

SymbolTableFrame* STSPEC2::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//OPTTAG : ID
OPTTAG1::OPTTAG1(tree* rawTree) {
    name = new ID(rawTree->subTrees[0], false, true, 0);
    lineNumber = rawTree->lineNumber;
}

Symbol* OPTTAG1::GetSymbol() {
    return name->symbol;
}

void OPTTAG1::SetFieldSymbols(SymbolTableFrame *fieldSymbols) {
    name->SetFieldSymbols(fieldSymbols);
}

SymbolTableFrame* OPTTAG1::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//OPTTAG :
OPTTAG2::OPTTAG2(tree* rawTree) {
    char* anonIdString = new char[10];
    sprintf(anonIdString, "%d", anonId++);
    string name = anonIdString;
    name = "anonstruct" + name;
    symbol = new Symbol(name, false, true, 0);
    lineNumber = rawTree->lineNumber;
}

Symbol* OPTTAG2::GetSymbol() {
    return symbol;
}

void OPTTAG2::SetFieldSymbols(SymbolTableFrame *fieldSymbols) {
    symbol->SetFieldSymbols(fieldSymbols);
}

SymbolTableFrame* OPTTAG2::GetFieldSymbols() {
    return symbol->GetFieldSymbols();
}

//VAR : ID
VAR1::VAR1(tree* rawTree, int dimension) {
    name = new ID(rawTree->subTrees[0], false, false, dimension);
    lineNumber = rawTree->lineNumber;
}

void VAR1::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    name->SetFieldSymbols(fieldSymbol);
}

string VAR1::GetName() {
    return name->symbol->name;
}

//VAR : VAR LB INT RB
VAR2::VAR2(tree* rawTree, int dimension) {
    var = VAR::createVAR(rawTree->subTrees[0], dimension + 1);
    num = new NUM(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

string VAR2::GetName() {
    return var->GetName();
}

void VAR2::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    var->SetFieldSymbols(fieldSymbol);
}

//FUNC : ID LP PARAS RP
FUNC::FUNC(tree* rawTree) {
    name = new ID(rawTree->subTrees[0], true, false, 0);
    symbolTable->EnterScope();
    paras = PARAS::createPARAS(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

void FUNC::SetFieldSymbols(SymbolTableFrame *fieldSymbols) {
    name->SetFieldSymbols(fieldSymbols);
}

SymbolTableFrame* FUNC::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//PARAS : PARA COMMA PARAS
PARAS1::PARAS1(tree* rawTree) {
    para = new PARA(rawTree->subTrees[0]);
    paras = PARAS::createPARAS(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

//PARAS : PARA
PARAS2::PARAS2(tree* rawTree) {
    para = new PARA(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//PARAS :
PARAS3::PARAS3(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

//PARA : SPEC VAR
PARA::PARA(tree* rawTree) {
    spec = SPEC::createSPEC(rawTree->subTrees[0]);
    var = VAR::createVAR(rawTree->subTrees[1], 0);
    var->SetFieldSymbols(spec->GetFieldSymbols());
    lineNumber = rawTree->lineNumber;
}

string PARA::GetName() {
    return var->GetName();
}

//STMTBLOCK : LC DEFS STMTS RC
STMTBLOCK::STMTBLOCK(tree* rawTree) {
    symbolTable->EnterScope();
    defs = DEFS::createDEFS(rawTree->subTrees[1]);
    stmts = STMTS::createSTMTS(rawTree->subTrees[2]);
    symbolTable->ExitScope();
    lineNumber = rawTree->lineNumber;
}

//STMTS : STMT STMTS
STMTS1::STMTS1(tree* rawTree) {
    stmt = STMT::createSTMT(rawTree->subTrees[0]);
    stmts = STMTS::createSTMTS(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

//STMTS :
STMTS2::STMTS2(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

//STMT : EXP SEMI
STMT1::STMT1(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//STMT : STMTBLOCK
STMT2::STMT2(tree* rawTree) {
    stmtblock = new STMTBLOCK(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//STMT : RETURN EXP SEMI
STMT3::STMT3(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

//STMT : IF LP EXP RP STMT ESTMT
STMT4::STMT4(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[2]);
    stmt = STMT::createSTMT(rawTree->subTrees[4]);
    estmt = ESTMT::createESTMT(rawTree->subTrees[5]);
    lineNumber = rawTree->lineNumber;
}

//STMT : FOR LP FOREXP SEMI FOREXP SEMI FOREXP RP STMT
STMT5::STMT5(tree* rawTree) {
    forexp1 = FOREXP::createFOREXP(rawTree->subTrees[2]);
    forexp2 = FOREXP::createFOREXP(rawTree->subTrees[4]);
    forexp3 = FOREXP::createFOREXP(rawTree->subTrees[6]);
    stmt = STMT::createSTMT(rawTree->subTrees[8]);
    lineNumber = rawTree->lineNumber;
}

//CONT SEMI
STMT6::STMT6(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

//BREAK SEMI
STMT7::STMT7(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

//ESTMT : ELSE STMT
ESTMT1::ESTMT1(tree* rawTree) {
    stmt = STMT::createSTMT(rawTree->subTrees[1]);
    isEmpty = false;
    lineNumber = rawTree->lineNumber;
}

//ESTMT :
ESTMT2::ESTMT2(tree* rawTree) {
    isEmpty = true;
    lineNumber = rawTree->lineNumber;
}

//DEFS : DEF DEFS
DEFS1::DEFS1(tree* rawTree) {
    def = new DEF(rawTree->subTrees[0]);
    defs = DEFS::createDEFS(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

//DEFS :
DEFS2::DEFS2(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

//DEF : SPEC DECS SEMI
DEF::DEF(tree* rawTree) {
    spec = SPEC::createSPEC(rawTree->subTrees[0]);
    decs = DECS::createDECS(rawTree->subTrees[1]);
    decs->SetFieldSymbols(spec->GetFieldSymbols());
    lineNumber = rawTree->lineNumber;
}

//DECS : DEC COMMA DECS
DECS1::DECS1(tree* rawTree) {
    dec = DEC::createDEC(rawTree->subTrees[0]);
    decs = DECS::createDECS(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

void DECS1::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    dec->SetFieldSymbols(fieldSymbol);
    decs->SetFieldSymbols(fieldSymbol);
}

//DECS : DEC
DECS2::DECS2(tree* rawTree) {
    dec = DEC::createDEC(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

void DECS2::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    dec->SetFieldSymbols(fieldSymbol);
}

//DEC : VAR
DEC1::DEC1(tree* rawTree) {
    var = VAR::createVAR(rawTree->subTrees[0], 0);
    lineNumber = rawTree->lineNumber;
}

void DEC1::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    var->SetFieldSymbols(fieldSymbol);
}

//DEC : VAR ASSIGNOP INIT
DEC2::DEC2(tree* rawTree) {
    var = VAR::createVAR(rawTree->subTrees[0], 0);
    init = INIT::createINIT(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

void DEC2::SetFieldSymbols(SymbolTableFrame *fieldSymbol) {
    var->SetFieldSymbols(fieldSymbol);
}

//INIT : EXP
INIT1::INIT1(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//INIT : LC ARGS RC
INIT2::INIT2(tree* rawTree) {
    args = ARGS::createARGS(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

//FOREXP : EXP
FOREXP1::FOREXP1(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//FOREXP :
FOREXP2::FOREXP2(tree* rawTree) {}

//EXP : EXP BINARYOP EXP
EXP1::EXP1(tree* rawTree) {
    exp1 = EXP::createEXP(rawTree->subTrees[0]);
    op = new OP(rawTree->subTrees[1]);
    exp2 = EXP::createEXP(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

string EXP1::GetIDName() {
    return "";
}

SymbolTableFrame* EXP1::GetFieldSymbols() {
    return NULL;
}

//EXP : UNARYOP EXP
EXP2::EXP2(tree* rawTree) {
    op = new OP(rawTree->subTrees[0]);
    exp = EXP::createEXP(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

string EXP2::GetIDName() {
    return "";
}

SymbolTableFrame* EXP2::GetFieldSymbols() {
    return NULL;
}

//EXP : EXP : '-' EXP
EXP3::EXP3(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

string EXP3::GetIDName() {
    return "";
}

SymbolTableFrame* EXP3::GetFieldSymbols() {
    return NULL;
}

//EXP : LP EXP RP
EXP4::EXP4(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[1]);
    lineNumber = rawTree->lineNumber;
}

string EXP4::GetIDName() {
    return exp->GetIDName();
}

SymbolTableFrame* EXP4::GetFieldSymbols() {
    return exp->GetFieldSymbols();
}

//EXP : ID LP ARGS RP
EXP5::EXP5(tree* rawTree) {
    name = new ID(rawTree->subTrees[0], 0);
    args = ARGS::createARGS(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

string EXP5::GetIDName() {
    return name->symbol->name;
}

SymbolTableFrame* EXP5::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//EXP : ID ARRS
EXP6::EXP6(tree* rawTree) {
    arrs = ARRS::createARRS(rawTree->subTrees[1]);
    name = new ID(rawTree->subTrees[0], arrs->Dimension());
    lineNumber = rawTree->lineNumber;
}

string EXP6::GetIDName() {
    return name->symbol->name;
}

SymbolTableFrame* EXP6::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//EXP : EXP DOT ID
EXP7::EXP7(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[0]);
    SymbolTableFrame* fieldSymbols = exp->GetFieldSymbols();
    if(fieldSymbols == NULL)
    {
        cout << "Line " << rawTree->lineNumber << " Try to access element of non-struct." << endl;
    }
    else {
        fieldSymbols->owner = exp->GetIDName();
    }
    name = new ID(rawTree->subTrees[2], fieldSymbols, 0);
    lineNumber = rawTree->lineNumber;
}

string EXP7::GetIDName() {
    return exp->GetIDName();
}

SymbolTableFrame* EXP7::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//EXP : INT
EXP8::EXP8(tree* rawTree) {
    num = new NUM(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

string EXP8::GetIDName() {
    return "";
}

SymbolTableFrame* EXP8::GetFieldSymbols() {
    return NULL;
}

//EXP : ID ARRS ASSIGNOP EXP
EXP9::EXP9(tree* rawTree) {
    arrs = ARRS::createARRS(rawTree->subTrees[1]);
    name = new ID(rawTree->subTrees[0], arrs->Dimension());
    exp = EXP::createEXP(rawTree->subTrees[3]);
    op = getContent(rawTree->subTrees[2]->symbol);
    lineNumber = rawTree->lineNumber;
}

string EXP9::GetIDName() {
    return name->symbol->name;
}

SymbolTableFrame* EXP9::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//EXP : EXP DOT ID ASSIGNOP EXP
EXP10::EXP10(tree* rawTree) {
    exp1 = EXP::createEXP(rawTree->subTrees[0]);
    //cout << (exp1->GetFieldSymbols() == NULL) << endl;
    name = new ID(rawTree->subTrees[2], exp1->GetFieldSymbols(), 0);
    exp2 = EXP::createEXP(rawTree->subTrees[4]);
    op = getContent(rawTree->subTrees[3]->symbol);
    lineNumber = rawTree->lineNumber;
}

string EXP10::GetIDName() {
    return name->symbol->name;
}

SymbolTableFrame* EXP10::GetFieldSymbols() {
    return name->GetFieldSymbols();
}

//ARRS : LB EXP RB ARRS
ARRS1::ARRS1(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[1]);
    arrs = ARRS::createARRS(rawTree->subTrees[3]);
    lineNumber = rawTree->lineNumber;
}

bool ARRS1::isEmpty() {
    return false;
}

int ARRS1::Dimension() {
    return 1 + arrs->Dimension();
}

//ARRS :
ARRS2::ARRS2(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

bool ARRS2::isEmpty() {
    return true;
}

int ARRS2::Dimension() {
    return 0;
}

//ARGS : EXP COMMA ARGS
ARGS1::ARGS1(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[0]);
    args = ARGS::createARGS(rawTree->subTrees[2]);
    lineNumber = rawTree->lineNumber;
}

//ARGS : EXP
ARGS2::ARGS2(tree* rawTree) {
    exp = EXP::createEXP(rawTree->subTrees[0]);
    lineNumber = rawTree->lineNumber;
}

//ARGS :
ARGS3::ARGS3(tree* rawTree) {
    lineNumber = rawTree->lineNumber;
}

char* ParseTree::getContent(const char *nodeName) {
    int end = 0;
    while(nodeName[++end] != '(');
    char* name = new char[end];
    for(int i = 0; i < end; ++i) {
        name[i] = nodeName[i];
    }
    name[end] = '\0';
    
    return name;
}

ID::ID(tree* rawTree, bool isFunction, bool isType, int dimension) {
    string symbolId = getContent(rawTree->symbol);
    symbol = symbolTable->RegisterSymbol(symbolId, isFunction, isType, dimension);
    if(symbol == NULL) {
        cout << "in line " << rawTree->lineNumber << "." << endl;
    }
    fieldSymbols = NULL;
    lineNumber = rawTree->lineNumber;
}

ID::ID(tree* rawTree, int dimension) {
    string symbolId = getContent(rawTree->symbol);
    symbol = symbolTable->Get(symbolId);
    if(symbol == NULL) {
        cout << "in line " << rawTree->lineNumber << "." << endl;
    }
    lineNumber = rawTree->lineNumber;
    fieldSymbols = NULL;
    this->dimension = dimension;
    lineNumber = rawTree->lineNumber;
}

ID::ID(tree* rawTree, SymbolTableFrame* fieldSymbols, int dimension) {
    string symbolId = getContent(rawTree->symbol);
    symbol = fieldSymbols->GetInCurrFrame(symbolId);
    if(symbol == NULL) {
        cout << "Line " << rawTree->lineNumber << " Struct " << fieldSymbols->owner << " dosen't have a field called " << symbolId << "." << endl;
    }
    this->fieldSymbols = NULL;
    this->dimension = dimension;
    lineNumber = rawTree->lineNumber;
}

void ID::SetFieldSymbols(SymbolTableFrame *fieldSymbols) {
    symbol->SetFieldSymbols(fieldSymbols);
}

SymbolTableFrame* ID::GetFieldSymbols() {
    if(dimension == symbol->dimension) {
        return symbol->GetFieldSymbols();
    }
    else {
        return NULL;
    }
}

NUM::NUM(tree* rawTree) {
    char* numChar;
    num = 0;
    int i = 0;
    numChar = ParseTree::getContent(rawTree->symbol);
    int base = 10;
    if(numChar[1] == 'x' || numChar[1] == 'X') {
        base = 16;
        i = 2;
    }
    else if(numChar[0] == '0') {
        base = 8;
    }
    for(; i < strlen(numChar); ++i) {
        num = base * num;
        if(numChar[i] >= 'a' && numChar[i] <= 'z') {
            num += numChar[i] - 'a' + 10;
        }
        else if(numChar[i] >= 'A' && numChar[i] <= 'Z') {
            num += numChar[i] - 'A' + 10;
        }
        else {
            num += numChar[i] - '0';
        }
    }
    lineNumber = rawTree->lineNumber;
}

OP::OP(tree* rawTree) {
    op = ParseTree::getContent(rawTree->symbol);
    lineNumber = rawTree->lineNumber;
}

TYPE::TYPE(tree* rawTree) {
    type = ParseTree::getContent(rawTree->symbol);
    lineNumber = rawTree->lineNumber;
}