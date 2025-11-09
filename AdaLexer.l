%{
#include "tokens.h"
#include <string.h>
#include <stdio.h>

void yyerror(const char *s);
YYSTYPE yylval;
%}

/* %option caseless */

%%

"--".*                               { /* Comment */ }
[ \t\r]+                             { /* Skip whitespace */ }
\n                                   { /* Skip newline */ }


[0-9]+                               { yylval.ival = atoi(yytext); return INTEGER_LITERAL; }

[A-Za-z][A-Za-z0-9_]*                {
    // Check if identifier is actually a keyword
    if (strcmp(yytext, "procedure") == 0) return PROCEDURE;
    if (strcmp(yytext, "Main") == 0) return MAIN;
    if (strcmp(yytext, "is") == 0) return IS;
    if (strcmp(yytext, "begin") == 0) return BEGIN_TOKEN;
    if (strcmp(yytext, "end") == 0) return END;
    if (strcmp(yytext, "if") == 0) return IF;
    if (strcmp(yytext, "then") == 0) return THEN;
    if (strcmp(yytext, "else") == 0) return ELSE;
    if (strcmp(yytext, "while") == 0) return WHILE;
    if (strcmp(yytext, "loop") == 0) return LOOP;
    if (strcmp(yytext, "Put_Line") == 0) return PUT_LINE;
    if (strcmp(yytext, "Get_Line") == 0) return GET_LINE;
    if (strcmp(yytext, "and") == 0) return AND;
    if (strcmp(yytext, "or") == 0) return OR;
    if (strcmp(yytext, "not") == 0) return NOT;
    if (strcmp(yytext, "xor") == 0) return XOR;
    if (strcmp(yytext, "true") == 0) return BOOLEAN_LITERAL;
    if (strcmp(yytext, "false") == 0) return BOOLEAN_LITERAL;
    
    yylval.text = strdup(yytext);
    return IDENTIFIER;
}

":="                                 { return ASSIGN; }
"="                                  { return EQ; }
"/="                                 { return NEQ; }
"<="                                 { return LE; }
">="                                 { return GE; }
"<"                                  { return LT; }
">"                                  { return GT; }
"+"                                  { return PLUS; }
"*"                                  { return TIMES; }
"/"                                  { return DIVIDE; }
"("                                  { return LPAREN; }
")"                                  { return RPAREN; }
";"                                  { return SEMI; }
":"                                  { return COLON; }
[.]                                  { return DOT; }
","                                  { return COMMA; }
"-"                                  { return MINUS; }

.                                    { printf("UNKNOWN: %s\n", yytext); }

%%

int yywrap(void) { return 1; }

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}