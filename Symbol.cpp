#include "Symbol.h"
#include <string>

/*
 Constructor for a symbol
 */

Symbol::Symbol(std::string name, bool isFunction, bool isType, int dimension)
    : name(name), isFunction(isFunction), isType(isType), type(NULL), dimension(dimension), isGlobal(false), sideEffectFunction(false) {}