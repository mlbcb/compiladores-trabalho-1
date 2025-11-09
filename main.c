#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "ast.h"
extern FILE* yyin;
extern int yyparse(void);
extern Stm root;

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
        print_stm(root);
    }

    fclose(yyin);
    return 0;
}