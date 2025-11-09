all: compiler

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: AdaLexer.l parser.tab.h
	flex AdaLexer.l

compiler: main.c lex.yy.c parser.tab.c parser.tab.h ast.c
	gcc -Wall -g -o compiler main.c lex.yy.c parser.tab.c parser.tab.h ast.c

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c
