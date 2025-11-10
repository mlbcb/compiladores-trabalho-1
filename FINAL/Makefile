all: compiler

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

compiler: main.c lex.yy.c parser.tab.c parser.tab.h ast.c
	gcc -g -o compiler main.c lex.yy.c parser.tab.c parser.tab.h ast.c

test: ./compiler
	./compiler tests/test1.ada
	./compiler tests/test2.ada
	./compiler tests/test3.ada
	./compiler tests/test5.ada

test_fail: ./compiler
	./compiler tests/test4.ada
	
clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c