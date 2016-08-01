#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include <iostream>
#include <vector>
#include "GlobalDefinition.h"
#include "fstream"

/*
 Define the Module class
 */

class GlobalDefinition;
class Module {
private:
    std::vector<GlobalDefinition*> definitions;
public:
    void Add(GlobalDefinition* definition);
    void Emit(ofstream& os);
    void Optimize();
};

#endif