all: compiler

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

compiler: main.c lex.yy.c parser.tab.c parser.tab.h ast.c
	gcc -g -o compiler main.c lex.yy.c parser.tab.c parser.tab.h ast.c

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c