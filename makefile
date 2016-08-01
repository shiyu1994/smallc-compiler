all:lex.yy.c y.tab.c y.tab.h scc
g++ -std=c++0x *.cpp -o output
y.tab.h y.tab.c : Syntax.y
	yacc -d Syntax.y
lex.yy.c : Lexical.l
	flex Lexical.l
scc : lex.yy.c y.tab.c
	g++ -x c lex.yy.c y.tab.c -x c++ main.cpp BasicBlock.cpp CodeGenerator.cpp Function.cpp GlobalDefinition.cpp Instruction.cpp Module.cpp Namer.cpp Symbol.cpp SymbolTable.cpp Type.cpp Typer.cpp -o scc

clean:
	rm scc