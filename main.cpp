//
//  main.cpp
//  CToLLVM
//
//  Created by Shi Yu on 16/1/12.
//  Copyright (c) 2016年 Shi Yu. All rights reserved.
//

#include <iostream>
#include "ParseTree.h"
#include "common.h"

int main(int argc, const char * argv[]) {

    ofstream fout(argv[2]);
    
    if(!fout) {
        cerr << "File " << argv[2] << " cannot be founded." << endl;
    }
    
    tree *parseTreeRoot;
    parseTreeRoot = parseEntry(argv[1]);
    PROGRAM* program = new PROGRAM(parseTreeRoot);
    program->Typer();
    program->Gen();
    program->Optimize();
    program->Emit(fout);
    
    return 0;
}
