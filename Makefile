CC = g++
LIBS = -ll
LEX = lex
YACC = yacc
CFLAGS = -DYYDEBUG=1
all: ast
ast: y.tab.c lex.yy.c ast.cpp
	$(CC) -o ast y.tab.c lex.yy.c ast.cpp $(LIBS)
y.tab.c: ast.y
	$(YACC) -d example.y
lex.yy.c : ast.l
	$(LEX) example-07.l