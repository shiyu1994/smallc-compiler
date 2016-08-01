%{
    /*
    This is the yacc input to generate parser. It calls yylex() to get the tokens. The generated parser will print a parse tree into a file.
     */
    
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "common.h"
    
    int yywrap(void);
    
    int yylex();
    
    tree* parseEntry(char const* sourceFile/*, char const* outputFile*/);
    
    void yyerror(char const*);
    
    //The stack node, in a doubly linked way.
    struct StackNode {
        int position;
        struct StackNode* next;
        struct StackNode* prev;
    };
    
    //The stack used to identify the parenthesis mismatch
    typedef struct sta {
        struct StackNode* top;
    } stack;
    
    //Allocate space for a stack
    stack* initStack();
    
    //Push element into a stack
    void push(stack* s, int newElem);
    
    //Pop element out of stack
    int pop(stack* s);
    
    extern FILE *yyin, *yyout;
    
    //Create a leaf node in the parse tree for a terminal
    extern tree* createLeaf(char const*, int linenumber);
    
    //Create a internal node in the parse tree for a nonterminal
    void createNode(tree*, char const*, int);
    
    //Print the parse tree
    void printTree(tree* root, int level);
    
    extern int yylineno;
    
    //Stack for detecting unmatched '('
    stack* globalStackP;
    
    //Stack for detecting unmatched '['
    stack* globalStackB;
    
    //Stack for detecting curly unmatched '{'
    stack* globalStackC;
    
    //A flag to indicate whether a mismatch has occurred
    int missMatch;
    
    //The number of errors
    int errorCount;
    
    tree* root;
%}

/*
 Define the tokens, they are all parse tree nodes.
*/
%token <node> INT
%token <node> ID
%token <node> SEMI
%token <node> COMMA
%token <node> TYPE
%token <node> LP
%token <node> RP
%token <node> LB
%token <node> RB
%token <node> LC
%token <node> RC
%token <node> STRUCT
%token <node> RETURN
%token <node> IF
%token <node> ELSE
%token <node> BREAK
%token <node> CONT
%token <node> FOR
%token <node> error
/*
 Define various operators, their associativity and precedence.
 The '-' is separated from normal binary operators, because it can also be an unary operator. The syntax analyzer will determine whether it is binary or unary.
*/
%right <node> ASSIGNOP
%left <node> BINARYOP10
%left <node> BINARYOP9
%left <node> BINARYOP8
%left <node> BINARYOP7
%left <node> BINARYOP6
%left <node> BINARYOP5
%left <node> BINARYOP4
%left <node> BINARYOP3
%left <node> BINARYOP2 '-'
%left <node> BINARYOP1

%right <node> UNARYOP

%left <node> DOT

%start PROGRAM

/*
 Define the type of yylval. In my case, it has only a node pointer.
 */
%union {
    tree *node;
};

/*
 Define the types of nonterminals as parse tree node.
 */
%type <node> PROGRAM EXTDEFS EXTDEF EXTVARS DEC SPEC STSPEC OPTTAG VAR FUNC PARAS PARA STMTBLOCK STMTS STMT ESTMT DEFS DEF DECS INIT FOREXP EXP ARRS ARGS enterLC enterLP leavingRC leavingRP enterLB leavingRB
%%

/*
 The following part is definitions of syntax rules and their actions.
 For each nonterminal, we create an internal node. The node takes nodes of nonterminals in the production body as children
*/

/*
 When the PROGRAM symbol is reduced, set its node as the root.
 */
PROGRAM : EXTDEFS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "PROGRAM", 1);
    ($$ -> subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
    root = $$;
}
;

EXTDEFS : EXTDEF EXTDEFS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTDEFS", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTDEFS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

EXTDEF : SPEC EXTVARS SEMI {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTDEF", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
//Add an error detection for missing ';'.
| SPEC EXTVARS error {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
| SPEC FUNC STMTBLOCK {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTDEF", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

EXTVARS : DEC {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTVARS", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| DEC COMMA EXTVARS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTVARS", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXTVARS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 3;
    $$->lineNumber = yylineno;
}
;

SPEC : TYPE {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "SPEC", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| STSPEC {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "SPEC", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

//enterLC and leavingRC are nonterminals to detect unmatched '{'. I add these two nonterminals to make sure that some actions can immediately happen when a curly brace is founded.
STSPEC : STRUCT OPTTAG enterLC DEFS leavingRC {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STSPEC", 5);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    ($$->subTrees)[4] = $5;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| STRUCT ID {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STSPEC", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

OPTTAG : ID {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "OPTTAG", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "OPTTAG", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

VAR : ID {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "VAR", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
//enterLB and leavingRB are nonterminals to detect unmatched '['. I add these two nonterminals to make sure that some actions can immediately happen when a bracket is founded.
| VAR enterLB INT leavingRB {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "VAR", 4);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

//enterLP and RCorError are nonterminals to detect unmatched '('. I add these two nonterminals to make sure that some actions can immediately happen when a parenthesis is founded.
FUNC : ID enterLP PARAS leavingRP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "FUNC", 4);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
;

PARAS : PARA COMMA PARAS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "PARAS", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| PARA {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "PARAS", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "PARAS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 3;
    $$->lineNumber = yylineno;
}
;

PARA : SPEC VAR {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "PARA", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
;

//enterLC and leavingRC are nonterminals to detect unmatched '{'. I add these two nonterminals to make sure that some actions can immediately happen when a curly brace is founded.
STMTBLOCK : enterLC DEFS STMTS leavingRC {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMTBLOCK", 4);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
;

STMTS : STMT STMTS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMTS", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMTS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

STMT : EXP SEMI {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
//Add an error detection for missing ';'.
| EXP error {
    if(!missMatch) {
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
    }
}
| STMTBLOCK {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
| RETURN EXP SEMI {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 3;
    $$->lineNumber = yylineno;
}
//Add an error detection for missing ';'.
| RETURN EXP error {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
//enterLP and RCorError are nonterminals to detect unmatched '('. I add these two nonterminals to make sure that some actions can immediately happen when a parenthesis is founded.
| IF enterLP EXP leavingRP STMT ESTMT {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 6);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    ($$->subTrees)[4] = $5;
    ($$->subTrees)[5] = $6;
    $$->productionId = 4;
    $$->lineNumber = yylineno;
}
//enterLP and RCorError are nonterminals to detect unmatched '('. I add these two nonterminals to make sure that some actions can immediately happen when a parenthesis is founded.
| FOR enterLP FOREXP SEMI FOREXP SEMI FOREXP leavingRP STMT {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 9);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    ($$->subTrees)[4] = $5;
    ($$->subTrees)[5] = $6;
    ($$->subTrees)[6] = $7;
    ($$->subTrees)[7] = $8;
    ($$->subTrees)[8] = $9;
    $$->productionId = 5;
    $$->lineNumber = yylineno;
}
| CONT SEMI {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 6;
    $$->lineNumber = yylineno;
}
//Add an error detection for missing ';'.
| CONT error {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
| BREAK SEMI {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "STMT", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 7;
    $$->lineNumber = yylineno;
}
//Add an error detection for missing ';'.
| BREAK error {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
;

ESTMT : ELSE STMT {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ESTMT", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ESTMT", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

DEFS : DEF DEFS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DEFS", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DEFS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

DEF : SPEC DECS SEMI {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DEF", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
//Add an error detection for missing ';'.
| SPEC DECS error {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
;

DECS : DEC COMMA DECS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DECS", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| DEC {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DECS", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

DEC : VAR {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DEC", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| VAR ASSIGNOP INIT {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "DEC", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

//The righthand side expression of a initialization can be empty, so we use FOREXP instead of EXP. NO!!
INIT : EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "INIT", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
//enterLC and leavingRC are nonterminals to detect unmatched '{'. I add these two nonterminals to make sure that some actions can immediately happen when a curly brace is founded.
| enterLC ARGS leavingRC {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "INIT", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

//FOREXP is either an EXP or empty, this nonterminal is used in cases where an expression can be empty, for example in the head of 'for' loop. So we give it the name FOREXP
FOREXP : EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "FOREXP", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "FOREXP", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

/*
 We separate operators of different precedences, by adding more nonterminals for binary operators.
*/
EXP : EXP BINARYOP1 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP2 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP '-' EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = createLeaf("-(BINARYOP2)", yylineno);
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
} %prec BINARYOP2 //When '-' is used as binary operator, we give it the same associativity and precedence with '+'
| EXP BINARYOP3 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP4 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP5 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP6 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP7 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP8 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP9 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP BINARYOP10 EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| UNARYOP EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
| '-' EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 2);
    ($$->subTrees)[0] = createLeaf("-(UNARYOP)", yylineno);
    ($$->subTrees)[1] = $2;
    $$->productionId = 3;
    $$->lineNumber = yylineno;
}   %prec UNARYOP //When '-' is used as unary operator, we give it the same precedence and associativity as other unary operators.

//enterLP and RCorError are nonterminals to detect unmatched '('. I add these two nonterminals to make sure that some actions can immediately happen when a parenthesis is founded.
| enterLP EXP leavingRP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 4;
    $$->lineNumber = yylineno;
}
//enterLP and RCorError are nonterminals to detect unmatched '('. I add these two nonterminals to make sure that some actions can immediately happen when a parenthesis is founded.
| ID enterLP ARGS leavingRP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 4);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    $$->productionId = 5;
    $$->lineNumber = yylineno;
}
| ID ARRS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 2);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    $$->productionId = 6;
    $$->lineNumber = yylineno;
}
| EXP DOT ID {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 7;
    $$->lineNumber = yylineno;
}
| INT {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 8;
    $$->lineNumber = yylineno;
}
//I distinguish '=' '+=' '-=' and other assign operators with binary operators. So need rules for assign operations in expressions.
| ID ARRS ASSIGNOP EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 4);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    $$->productionId = 9;
    $$->lineNumber = yylineno;
}
| EXP DOT ID ASSIGNOP EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "EXP", 5);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    ($$->subTrees)[4] = $5;
    $$->productionId = 10;
    $$->lineNumber = yylineno;
}
;

//enterLB and leavingRB are nonterminals to detect unmatched '['. I add these two nonterminals to make sure that some actions can immediately happen when a bracket is founded.
ARRS : enterLB EXP leavingRB ARRS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ARRS", 4);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    ($$->subTrees)[3] = $4;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ARRS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
;

ARGS : EXP COMMA ARGS {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ARGS", 3);
    ($$->subTrees)[0] = $1;
    ($$->subTrees)[1] = $2;
    ($$->subTrees)[2] = $3;
    $$->productionId = 1;
    $$->lineNumber = yylineno;
}
| EXP {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ARGS", 1);
    ($$->subTrees)[0] = $1;
    $$->productionId = 2;
    $$->lineNumber = yylineno;
}
| {
    $$ = (tree*)malloc(sizeof(tree));
    createNode($$, "ARGS", 1);
    ($$->subTrees)[0] = NULL;
    $$->productionId = 3;
    
}

//enterLC and leavingRC are nonterminals to detect unmatched '{'. I add these two nonterminals to make sure that some actions can immediately happen when a curly brace is founded.
enterLC : LC {
    $$ = $1;
    push(globalStackC, yylineno);
}

leavingRC : RC {
    pop(globalStackC);
    $$ = $1;
}
| error {
    if(globalStackC->top->prev != NULL && !missMatch) {
        missMatch = 1;
        fprintf(stderr, "Missing matched '}' for the '{' in line %d.\n", pop(globalStackC));
    }
}

//enterLB and leavingRB are nonterminals to detect unmatched '['. I add these two nonterminals to make sure that some actions can immediately happen when a bracket is founded.
enterLB : LB {
    $$ = $1;
    push(globalStackB, yylineno);
}

leavingRB : RB {
    $$ = $1;
    pop(globalStackB);
}
| error {
    if(globalStackB->top->prev != NULL && !missMatch) {
        missMatch = 1;
        fprintf(stderr, "Missing matched ']' for the '[' in line %d.\n", pop(globalStackB));
    }
}

//enterLP and RCorError are nonterminals to detect unmatched '('. I add these two nonterminals to make sure that some actions can immediately happen when a parenthesis is founded.
enterLP : LP {
    $$ = $1;
    push(globalStackP, yylineno);
}

leavingRP : RP {
    $$ = $1;
    pop(globalStackP);
}
| error {
    if(globalStackP->top->prev != NULL && !missMatch) {
        missMatch = 1;
        fprintf(stderr, "Missing matched ')' for the '(' in line %d.\n", pop(globalStackP));
    }
}
;

%%

tree* parseEntry(char const* sourceFile/*, char const* outputFile*/)
{
    //Initializes three stacks used for parenthese detection.
    globalStackP = initStack();
    globalStackB = initStack();
    globalStackC = initStack();
    
    //Initialize variables used for error detection.
    missMatch = 0;
    errorCount = 0;
    yylineno = 1;
    
    //Open files.
    yyin = fopen(sourceFile, "r");
    if(!yyin) {
        fprintf(stderr, "No such file.\n");
        return NULL;
    }
    /*yyout = fopen(outputFile, "w");
    if(!yyout) {
        fprintf(stderr, "No such file.\n");
        return NULL;
    }*/
    if(yyparse()) {
        printf("Parse Error.\n");
    }
    else {
        if(errorCount > 0)
            printf("Parsing success with syntax error(s).\n");
        /*else
            printf("Parsing success.\n");*/
        //printTree(root, 0);
    }
    if(errorCount > 0) {
        printf("%d error(s) in total.\n", errorCount);
    }
    fclose(yyin);
    //fclose(yyout);
    return root;
}

//A recursive function for parse tree printing.
void printTree(tree* root, int level) {
    int i = 0;
    
    if(root != NULL) {
        
        for(i = 0; i < level; ++i) {
            fprintf(yyout, "%s", "----");
        }
    
        fprintf(yyout, "%s", "|");
        fprintf(yyout, "%s", root->symbol);
        fprintf(yyout, "%s", "\n");
    
        for(i = 0; i < root->childNum; ++i) {
            //The children should have one deeper level than parent.
            printTree((root->subTrees)[i], level + 1);
        }
    }
    
    return;
}

//Initialize a stack
stack* initStack() {
    //Allocate memory for stack
    stack* newStack = (stack*)malloc(sizeof(stack));
    newStack->top = (struct StackNode*)malloc(sizeof(struct StackNode));
    
    //Set the stack as empty
    newStack->top->next = newStack->top->prev = NULL;
    
    return newStack;
}

//Push an element into a stack
void push(stack* s, int newElem) {
    struct StackNode* tempNode = s->top;
    s->top->next = (struct StackNode*)malloc(sizeof(struct StackNode));
    s->top->next->position = newElem;
    s->top->next->next = NULL;
    s->top = s->top->next;
    s->top->prev = tempNode;
}

//Pop an element out of stack
int pop(stack* s) {
    if(s->top->prev != NULL) {
        struct StackNode* tempNode = s->top;
        int topElem = s->top->position;
        s->top = s->top->prev;
        s->top->next = NULL;
        free(tempNode);
        return topElem;
    }
    return -1;
}

//Create an internal parse tree node, with the nonterminal name and children number.
void createNode(tree* newTree, char const* nodeName, int childNum) {
    newTree->symbol = (char*)malloc(sizeof(char) * (strlen(nodeName) + 1));
    strcpy(newTree->symbol, nodeName);
    newTree->subTrees = (tree**)malloc(sizeof(tree*) * childNum);
    newTree->childNum = childNum;
}

void yyerror(char const* errorMessage) {
    ++errorCount;
    fprintf(stderr, "Syntax error.\n");
}

int yywrap(void){return 1;}

