%{
    /*
     This is the flex input to generate lexical analyzer. It recognizes the lexeme patterns and return tokens to the parser.
    */
    
    #include <string.h>
    #include "common.h"
    #include "y.tab.h"
    
    //Create a leaf node in the parse tree for a terminal
    extern tree* createLeaf(char const* leafName, int linenumber);
    
    //Concatenate the lexeme and TokenName into "lexeme(TokenName)"
    char* catToken(char const* ytext, char const* TokenName);
%}

ws [ \t\n\r]

digit [0-9]
digits {digit}+
/*
 Define integer as decimal, octal or hexadecimal
 */
integer {digits}|0x([0-7]|[a-zA-Z])+|0X({digit}|[a-zA-Z])+

_letter [a-zA-Z_]
id {_letter}({_letter}|{integer})*

binaryop1 [\*\/\%]
binaryop2 [\+]
binaryop3 \<\<|\>\>
binaryop4 \>|\>=|\<|\<=
binaryop5 ==|!=
binaryop6 &
binaryop7 \^
binaryop8 \|
binaryop9 &&
binaryop10 \|\|
assignop \+=|-=|\*=|\/=|&=|\^=|\|=|\<\<=|\>\>=|=

prefixincrement \+\+
prefixdecrement --
unaryop [!~]|{prefixincrement}|{prefixdecrement}

%%

"int" {
    yylval.node = createLeaf("int(TYPE)", yylineno);
    return(TYPE);
}

"struct" {
    yylval.node = createLeaf("struct(STRUCT)", yylineno);
    return(STRUCT);
}

"return" {
    yylval.node = createLeaf("return(RETURN)", yylineno);
    return(RETURN);
}

"if" {
    yylval.node = createLeaf("if(IF)", yylineno);
    return(IF);
}

"else" {
    yylval.node = createLeaf("else(ELSE)", yylineno);
    return(ELSE);
}

"break" {
    yylval.node = createLeaf("break(BREAK)", yylineno);
    return(BREAK);
}

"continue" {
    yylval.node = createLeaf("continue(CONT)", yylineno);
    return(CONT);
}

"for" {
    yylval.node = createLeaf("for(FOR)", yylineno);
    return(FOR);
}

{id} {
    yylval.node = createLeaf(catToken(yytext,"(ID)"), yylineno);
    return(ID);
}

{integer} {
    yylval.node = createLeaf(catToken(yytext, "(INT)"), yylineno);
    return(INT);
}

{ws} {
    //If the white space is a new line, we increase yylineno, this will be useful in error handling.
    if(*yytext == '\n' || *yytext == '\r') {
        ++yylineno;
    }
};

";" {
    yylval.node = createLeaf(";(SEMI)", yylineno);
    return(SEMI);
}

"," {
    yylval.node = createLeaf(",(COMMA)", yylineno);
    return(COMMA);
}

"." {
    yylval.node = createLeaf(".(DOT)", yylineno);
    return(DOT);
}

"-" {
    return('-');
}

{assignop} {
    yylval.node = createLeaf(catToken(yytext, "(ASSIGNOP)"), yylineno);
    return(ASSIGNOP);
}

{binaryop1} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP1)"), yylineno);
    return(BINARYOP1);
}

{binaryop2} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP2)"), yylineno);
    return(BINARYOP2);
}

{binaryop3} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP3)"), yylineno);
    return(BINARYOP3);
}

{binaryop4} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP4)"), yylineno);
    return(BINARYOP4);
}

{binaryop5} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP5)"), yylineno);
    return(BINARYOP5);
}

{binaryop6} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP6)"), yylineno);
    return(BINARYOP6);
}

{binaryop7} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP7)"), yylineno);
    return(BINARYOP7);
}

{binaryop8} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP8)"), yylineno);
    return(BINARYOP8);
}

{binaryop9} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP9)"), yylineno);
    return(BINARYOP9);
}

{binaryop10} {
    yylval.node = createLeaf(catToken(yytext, "(BINARYOP10)"), yylineno);
    return(BINARYOP10);
}

{unaryop} {
    yylval.node = createLeaf(catToken(yytext, "(UNARYOP)"), yylineno);
    return(UNARYOP);
}

"(" {
    yylval.node = createLeaf("((LP)", yylineno);
    return(LP);
}

")" {
    yylval.node = createLeaf(")(RP)", yylineno);
    return(RP);
}

"[" {
    yylval.node = createLeaf("[(LB)", yylineno);
    return(LB);
}

"]" {
    yylval.node = createLeaf("](RB)", yylineno);
    return(RB);
}

"{" {
    yylval.node = createLeaf("{(LC)", yylineno);
    return(LC);
}

"}" {
    yylval.node = createLeaf("}(RC)", yylineno);
    return(RC);
}

%%

//Concatenate the lexeme and TokenName into "lexeme(TokenName)"
char* catToken(char const* ytext, char const* TokenName) {
    char* content = (char*)malloc(sizeof(char) * (yyleng + strlen(TokenName) + 1));
    strcpy(content, yytext);
    strcat(content, TokenName);
    return content;
}

//Create a leaf node in the parse tree for a terminal
tree* createLeaf(char const* leafName, int linenumber) {
    tree* newLeaf = (tree*)malloc(sizeof(tree));
    newLeaf->childNum = 0;
    newLeaf->lineNumber = linenumber;
    newLeaf->symbol = (char*)malloc(sizeof(char)*(strlen(leafName) + 1));
    strcpy(newLeaf->symbol,leafName);
    return newLeaf;
}
