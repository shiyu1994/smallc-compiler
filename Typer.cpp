#include "ParseTree.h"
#include "Type.h"
#include <iostream>

/*
 Calculate types for each parse tree node, the corresponding productions are commented right above each Typer() method
 */

using namespace std;

TupleType* ParseTree::EMPTY_TYPE = new EmptyType();

//PROGRAM : EXTDEFS
void PROGRAM::Typer() {
    extdefs->Typer();
}

//EXTDEFS : EXTDEF EXTDEFS
void EXTDEFS1::Typer() {
    extdef->Typer();
    extdefs->Typer();
}

//EXTDEFS :
void EXTDEFS2::Typer() {}

//EXTDEF : SPEC EXTVARS SEMI
void EXTDEF1::Typer() {
    Type* specType = spec->Typer();
    extvars->Typer(specType);
}

//TODO check type consistence
//EXTDEF : SPEC FUNC STMTBLOCK
void EXTDEF2::Typer() {
    func->Typer(spec->Typer());
    stmtblock->Typer();
}

//EXTVARS : DEC
void EXTVARS1::Typer(Type* type) {
    dec->Typer(type);
}

//EXTVARS : DEC COMMA EXTVARS
void EXTVARS2::Typer(Type* type) {
    dec->Typer(type);
    extvars->Typer(type);
}

//EXTVARS :
void EXTVARS3::Typer(Type* type) {}

//SPEC : TYPE
Type* SPEC1::Typer() {
    specType = type->Typer();
    return specType;
}

//SPEC : STSPEC
Type* SPEC2::Typer() {
    specType = stspec->Typer();
    return specType;
}

//STSPEC : STRUCT OPTTAG LC DEFS RC
Type* STSPEC1::Typer() {
    Structure* structureType = new Structure(opttag->GetSymbol()->name);
    defs->Typer(structureType);
    opttag->Typer(structureType);
    return structureType;
}

//STSPEC : STRUCT ID
Type* STSPEC2::Typer() {
    return ((MetaType*)name->Typer())->containType;
}

//OPTTAG : ID
void OPTTAG1::Typer(Type* type) {
    type->typeName = name->symbol->name;
    name->Typer(new MetaType(type));
}

//OPTTAG :
void OPTTAG2::Typer(Type* type) {
    type->typeName = symbol->name;
    symbol->type = new MetaType(type);
}

//VAR : ID
Type* VAR1::Typer(Type* type, Structure* structureType) {
    name->Typer(type);
    if(structureType != NULL) {
        structureType->Collect(name->symbol->name, type);
        return structureType;
    }
    return type;
}

//VAR : VAR LB INT RB
Type* VAR2::Typer(Type* type, Structure* structureType) {
    num->Typer();
    if(structureType != NULL) {
        return var->Typer(new Array(type, num->num), structureType);
    }
    return var->Typer(new Array(type, num->num), NULL);
}

//FUNC : ID LP PARAS RP
Type* FUNC::Typer(Type* type) {
    FuncType* funcType = new FuncType(paras->Typer(), type);
    name->Typer(funcType);
    return funcType;
}

//PARAS : PARA COMMA PARAS
Structure* PARAS1::Typer() {
    Structure* parasTypes = paras->Typer();
    parasTypes->Collect(para->GetName(), para->Typer());
    return parasTypes;
}

//PARAS : PARA
Structure* PARAS2::Typer() {
    Structure* structType = new Structure("");
    structType->Collect(para->GetName(), para->Typer());
    return structType;
}

//PARAS :
Structure* PARAS3::Typer() {
    return new Structure("");
}

//PARA : SPEC VAR
Type* PARA::Typer() {
    return var->Typer(spec->Typer(), NULL);
}

//STMTBLOCK : LC DEFS STMTS RC
Type* STMTBLOCK::Typer() {
    defs->Typer();
    return stmts->Typer();
}

//STMTS : STMT STMTS
Type* STMTS1::Typer() {
    Type* stmtType = stmt->Typer();
    Type* stmtsType = stmts->Typer();
    
    //TODO check for inconsistent return types
    if(stmtsType == EMPTY_TYPE) {
        return stmtType;
    }
    else {
        return stmtsType;
    }
}

//STMTS :
Type* STMTS2::Typer() {
    return EMPTY_TYPE;
}

//STMT : EXP SEMI
Type* STMT1::Typer() {
    exp->Typer();
    return EMPTY_TYPE;
}

//STMT : STMTBLOCK
Type* STMT2::Typer() {
    return stmtblock->Typer();
}

//STMT : RETURN EXP SEMI
Type* STMT3::Typer() {
    return exp->Typer();
}

//STMT : IF LP EXP RP STMT ESTMT
Type* STMT4::Typer() {
    exp->Typer();
    Type* thenType = stmt->Typer();
    Type* elseType = estmt->Typer();
    
    //TODO check for inconsistent return types;
    if(thenType == EMPTY_TYPE) {
        return elseType;
    }
    else {
        return thenType;
    }
}

//STMT : FOR LP FOREXP SEMI FOREXP SEMI FOREXP SEMI RP STMT
Type* STMT5::Typer() {
    forexp1->Typer();
    forexp2->Typer();
    forexp3->Typer();
    return stmt->Typer();
}

//STMT : CONT SEMI
Type* STMT6::Typer() {
    return EMPTY_TYPE;
}

//STMT : BREAK SEMI
Type* STMT7::Typer() {
    return EMPTY_TYPE;
}

//ESTMT : ELSE STMT
Type* ESTMT1::Typer() {
    return stmt->Typer();
}

//ESTMT :
Type* ESTMT2::Typer() {
    return EMPTY_TYPE;
}

//DEFS : DEF DEFS
void DEFS1::Typer(Type* type) {
    def->Typer(type);
    defs->Typer(type);
}

//DEFS :
void DEFS2::Typer(Type* type) {}

//DEF : SPEC DECS SEMI
void DEF::Typer(Type* type) {
    Type* specType = spec->Typer();
    if(type != EMPTY_TYPE) {
        decs->Typer(specType, (Structure*)type);
    }
    decs->Typer(specType, NULL);
}

//DECS : DEC DECS
void DECS1::Typer(Type* type, Structure* structureType) {
    dec->Typer(type, structureType);
    decs->Typer(type, structureType);
}

//DECS : DEC
void DECS2::Typer(Type* type, Structure* structureType) {
    dec->Typer(type, structureType);
}

//DEC : VAR
void DEC1::Typer(Type* type, Structure* structureType) {
    var->Typer(type, structureType);
}

//DEC : VAR ASSIGNOP INIT
void DEC2::Typer(Type* type, Structure* structureType) {
    var->Typer(type, structureType);
    init->Typer();
    
}

//INIT : EXP
Structure* INIT1::Typer() {
    Structure* structType = new Structure("");
    structType->Collect("", exp->Typer());
    return structType;
}

//INIT : LC ARGS RC
Structure* INIT2::Typer() {
    return args->Typer();
}

//FOREXP : EXP
Type* FOREXP1::Typer() {
    return exp->Typer();
}

//FOREXP :
Type* FOREXP2::Typer() {
    return EMPTY_TYPE;
}

//EXP : EXP BINARYOP EXP
Type* EXP1::Typer() {
    Type* type1 = exp1->Typer();
    Type* type2 = exp2->Typer();
    if(type1->typeName != "i32" || type2->typeName != "i32") {
        cout << "Line" << lineNumber << " Try to do arithmetic operation with type " <<
        type1->typeName << " and " << type2->typeName;
    }
    return type2;
}

//EXP : UNARYOP EXP
Type* EXP2::Typer() {
    Type* type = exp->Typer();
    if(type->typeName != "i32") {
        cout << "Line " << lineNumber << " Try to do arithmetic operation on type " << type->typeName << endl;
    }
    return type;
}

//EXP : '-' EXP
Type* EXP3::Typer() {
    Type* type = exp->Typer();
    if(type->typeName != "i32") {
        cout << "Line " << lineNumber << " Try to do arithmetic operation on type " << type->typeName << endl;
    }
    return type;
}

//EXP : LP EXP RP
Type* EXP4::Typer() {
    return exp->Typer();
}

//EXP : ID LP ARGS RP
Type* EXP5::Typer() {
    //Type check for function call is left to code generation phase
    return ((FuncType*)name->Typer())->returnType;
}

//EXP : ID ARRS
Type* EXP6::Typer() {
    Type* idType = name->Typer();
    if(!idType->isArray && !arrs->isEmpty()) {
        cout << "Line " << lineNumber << " Try to index a non-array variable "
        << name->symbol->name << endl;
    }
    return arrs->Typer(idType);
}

//EXP : EXP DOT ID
Type* EXP7::Typer() {
    Type* type = exp->Typer();
    if(!type->isStruct) {
        cout << "Line " << this->lineNumber << " Try to access element of a non-struct" << "." << endl;
    }
    Structure* structType = (Structure*)type;
    Type* elementType = structType->getElementType(name->symbol->name);
    if(elementType->typeName == "empty") {
        cout << "Line " << lineNumber << " Struct " << structType->typeName << " dosen't have a field called " << name->symbol->name << "." << endl;
    }
    
    return elementType;
}

//EXP : INT
Type* EXP8::Typer() {
    return num->Typer();
}

//EXP : ID ARRS ASSIGNOP EXP
Type* EXP9::Typer() {
    Type* idType = name->Typer();
    if(!idType->isArray && !arrs->isEmpty()) {
        cout << "Line " << lineNumber << " Try to index a non-array variable "
        << name->symbol->name << endl;
    }
    Type* arrayType = arrs->Typer(idType);
    Type* expType = exp->Typer();
    if(arrayType->typeName != expType->typeName) {
        cout << "Line " << lineNumber << " Try to assign " << idType->typeName << " with " << expType->typeName << "." << endl;
    }
    return arrayType;
}

//EXP : EXP DOT ID ASSIGNOP EXP
Type* EXP10::Typer() {
    Type* expType = exp1->Typer();
    if(!expType->isStruct) {
        cout << expType->typeName << endl;
        cout << "Line " << lineNumber << " Try to access element of a non-struct" << "." << endl;
    }
    Structure* structType = (Structure*)expType;
    Type* idType = structType->getElementType(name->symbol->name);
    if(idType->typeName == "empty") {
        cout << "Line " << lineNumber << " Struct " << structType->typeName << " dosen't have a field called " << name->symbol->name << "." << endl;
    }
    Type* exp2Type = exp2->Typer();
    if(exp2Type->typeName != idType->typeName) {
        cout << "Line " << lineNumber << " Try to assign " << idType->typeName << " with " << exp2Type->typeName << "." << endl;
    }
    return idType;
}

//TODO check type for indexes
//ARRS : LB EXP RB ARRS
Type* ARRS1::Typer(Type* type) {
    exp->Typer();
    return arrs->Typer(((Array*)type)->elementType);
}

//ARRS :
Type* ARRS2::Typer(Type* type) {
    return type;
}

//ARGS : EXP COMMA ARGS
Structure* ARGS1::Typer() {
    Structure* argsTypes = args->Typer();
    argsTypes->Collect("", exp->Typer());
    return argsTypes;
}

//ARGS : EXP
Structure* ARGS2::Typer() {
    Structure* structType = new Structure("");
    structType->Collect("", exp->Typer());
    return structType;
}

//ARGS :
Structure* ARGS3::Typer() {
    return new Structure("");
}


Type* ID::Typer(Type* type) {
    //cout << symbol->name << " "  << type->typeName << endl;
    if(type == EMPTY_TYPE) {
        return symbol->type;
    }
    else {
        symbol->type = type;
    }
    return type;
}

Type* TYPE::Typer() {
    return new Int();
}

Type* NUM::Typer() {
    return new Int();
}




