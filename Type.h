#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <vector>
#include <string>
#include <fstream>

/*
 Define data structures for types
 */

using namespace std;

class Type {
public:
    std::string typeName;
    bool isStruct;
    bool isArray;
    virtual void Emit(ofstream& os) = 0;
    bool isInt;
protected:
    Type(std::string typeName, bool isStruct, bool isArray)
    : typeName(typeName), isStruct(isStruct), isArray(isArray) {}
    Type() : isStruct(false), isArray(false), isInt(false) {}
};

//For int type
class Int : public Type {
public:
    Int() {isInt = true; typeName = "i32";};
    void Emit(ofstream& os);
};

//Array type, take another type as element type
class Array : public Type {
public:
    Type* elementType;
    int length;
    Array(Type* elementType, int length) : Type(elementType->typeName + "Array", false, true), elementType(elementType), length(length) {}
    void Emit(ofstream& os);
};

class NameTypePair;
//Structure type, contains the name of the struct and name and type of its elements
class Structure : public Type {
public:
    std::vector<NameTypePair*> elementTypes;
    Structure(std::string name) : Type(name, true, false) {};
    void Collect(std::string field, Type* type);
    Type* getElementType(std::string field);
    void Emit(ofstream& os);
};

//Type of type
class MetaType : public Type {
public:
    Type* containType;
    std::string typeName;
    MetaType(Type* containType) : containType(containType) {typeName = "meta";}
    void Emit(ofstream& os);
};

class TupleType : public Type {
private:
    Type* head;
    TupleType* tail;
public:
    TupleType(Type* head, TupleType* tail) : head(head), tail(tail) {}
    void Emit(ofstream& os);
};

class EmptyType : public TupleType {
public:
    EmptyType() : TupleType(NULL, NULL) { typeName = "empty"; }
    void Emit(ofstream& os);
};

//Type for function, including return type and parameter types
class FuncType : public Type {
public:
    Structure* paraType;
    Type* returnType;
    FuncType(Structure* paraType, Type* returnType) : paraType(paraType), returnType(returnType) {}
    void Emit(ofstream& os);
};

class NameTypePair {
friend class Structure;
public:
    std::string name;
    Type* type;
    NameTypePair(std::string name, Type* type) : name(name), type(type) {}
};

class Bool : public Type {
public:
    Bool() {};
    void Emit(ofstream& os);
};

#endif