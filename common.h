#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

/*
 This file defines the tree(node) structures used in flex input and yacc input.
 */

#include <stdlib.h>

/*
 The subtree struct (can also be regarded as node) used in parse tree.
 */
typedef struct tre {
    char* symbol;
    char* treeType;
    int childNum;
    struct tre** subTrees;
    int productionId;
    int lineNumber;
} tree;

//Create a leaf node in the parse tree for a terminal
extern tree* createLeaf(char const* leafName, int linenumber);
extern int yywrap(void);
extern tree* root;
extern tree* parseEntry(char const* sourceFile);

#endif //TREE_H_INCLUDED
