#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

extern int yyparse(void);
extern FILE* yyin;
extern void printAST();

int main(int argc, char** argv) {
    --argc; ++argv;
    if (argc != 0) {
        yyin = fopen(*argv, "r");
        if (!yyin) {
        printf("'%s': could not open file\n", *argv);
        return 1;
        }
    } //  yyin = stdin
    if (yyparse() == 0) {
        printf("Abstract Sintax Tree:\n");
        printAST();
    }

    fclose(yyin);
    return 0;

}