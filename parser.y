%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ast.h"

int yylex (void);
void yyerror (char const *);
%}

%union{
    int ival;
    float fval;
    char* text;
    int bval;
    Exp exp;
    Stm stm;
}

%type <exp> expr
%type <stm> stmt stmt_lst proc

/* tokens */
%token PROCEDURE
%token MAIN
%token IS
%token BEGIN_TOKEN
%token END

%token PUT_LINE GET_LINE

%token <ival> NUM
%token <fval> REAL
%token <text> ID
%token <bval> TRUE
%token <bval> FALSE

%token LPAREN RPAREN
%token SEMICOLON
%token COLON
%token ASSIGNMENT

%token EQUAL_TO DIFFERENT_THAN
%token GREATER_THAN LESS_THAN
%token EQUAL_OR_GREATER EQUAL_OR_LESS
%token AND OR NOT XOR

%token PLUS MINUS
%token TIMES DIVISION
%token MOD POWER REM

%token IF THEN ELSE 
%token WHILE LOOP

/*token precedence*/
%left AND OR XOR
%left EQUAL_TO DIFFERENT_THAN LESS_THAN EQUAL_OR_LESS GREATER_THAN EQUAL_OR_GREATER
%left PLUS MINUS 
%left TIMES DIVISION MOD REM
%right NOT POWER

%start top

%%

top 
    : proc { root = $1; }
    ;

proc 
    : PROCEDURE MAIN IS BEGIN_TOKEN stmt_lst END MAIN SEMICOLON { $$ = mk_proced($5); }
    ;

stmt_lst 
    : stmt_lst stmt { $$ = mk_compound($1, $2); }
    | stmt          { $$ = $1; }
    |               { $$ = NULL; }
    ;

stmt 
    : IF expr THEN stmt_lst ELSE stmt_lst END IF SEMICOLON { $$ = mk_if($2, $4, $5); }
    | IF expr THEN stmt_lst END IF SEMICOLON             { $$ = mk_if($2, $4, NULL); }
    | WHILE expr LOOP stmt_lst END LOOP SEMICOLON        { $$ = mk_while($2, $4); }
    | ID ASSIGNMENT expr SEMICOLON                       { $$ = mk_assign($1, $3); }   /* fixed */
    ;

expr
    : NUM                         { $$ = mk_numexp($1); }
    | REAL                        { $$ = mk_floatexp($1); }
    | ID                          { $$ = mk_idexp($1); }
    | TRUE                        { $$ = mk_boolexp(1); }
    | FALSE                       { $$ = mk_boolexp(0); }
    | LPAREN expr RPAREN          { $$ = mk_parenexp($2); }
    | expr EQUAL_TO expr          { $$ = mk_opexp($1, EQUAL_TO, $3); }
    | expr DIFFERENT_THAN expr    { $$ = mk_opexp($1, DIFFERENT_THAN, $3); }
    | expr GREATER_THAN expr      { $$ = mk_opexp($1, GREATER_THAN, $3); }
    | expr LESS_THAN expr         { $$ = mk_opexp($1, LESS_THAN, $3); }
    | expr EQUAL_OR_GREATER expr  { $$ = mk_opexp($1, EQUAL_OR_GREATER, $3); }
    | expr EQUAL_OR_LESS expr     { $$ = mk_opexp($1, EQUAL_OR_LESS, $3); }
    | expr AND expr               { $$ = mk_opexp($1, AND, $3); }
    | expr OR expr                { $$ = mk_opexp($1, OR, $3); }
    | expr XOR expr               { $$ = mk_opexp($1, XOR, $3); }
    | NOT expr                    { $$ = mk_opexp(NULL, NOT, $2); }  /* fixed */
    | expr PLUS expr              { $$ = mk_opexp($1, PLUS, $3); }
    | expr MINUS expr             { $$ = mk_opexp($1, MINUS, $3); }
    | expr TIMES expr             { $$ = mk_opexp($1, TIMES, $3); }
    | expr DIVISION expr          { $$ = mk_opexp($1, DIVISION, $3); }
    | expr MOD expr               { $$ = mk_opexp($1, MOD, $3); }
    | expr REM expr               { $$ = mk_opexp($1, REM, $3); }
    | expr POWER expr             { $$ = mk_opexp($1, POWER, $3); }
    ;

%%

void yyerror(char const *msg) {
    printf("parse error: %s\n", msg);
    exit(-1);
}
