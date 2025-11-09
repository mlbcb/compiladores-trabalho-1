%{
    #include "ast.h"
    Stm root;
%}
%union{
    int ival;
    float fval;
    char* text;
    int bval;
    Exp exps;
    Stm stms;
}

/* tokens */
%token PROCEDURE
%token MAIN
%token IS
%token BEGIN_TOKEN
%token END

%token PUT_LINE GET_LINE

%token <ival> NUM
%token <fval> REAL
%token <text> IDENTIFIER
%token <bval> TRUE FALSE


%token LPAREN RPAREN
%token SEMI
%token ASSIGN

%token EQ NEQ
%token GT LT
%token GE LE
%token AND OR NOT XOR

%token PLUS MINUS
%token TIMES DIVIDE
%token MOD POWER REM

%token IF THEN ELSE 
%token WHILE LOOP

/*token precedence*/
%left AND OR XOR
%left EQ NEQ LT LE GT GE
%left PLUS MINUS 
%left TIMES DIVIDE MOD REM
%right NOT POWER

%start top

%type <exps> expr
%type <stms> stmt stmt_lst proc top

%code requires{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"

    extern int yylex (void);
    extern void yyerror (char const *);
     
    extern Stm root;
}

%%

top : proc {root = $1;}
    ;

proc : PROCEDURE MAIN IS BEGIN_TOKEN stmt_lst END MAIN SEMI          {$$ = mk_proced($5);}
     ;

stmt_lst : stmt_lst stmt {$$ = mk_compound($1, $2);}
         | stmt          {$$ = $1;}
         ;

stmt : IF expr THEN stmt_lst ELSE stmt_lst END IF SEMI  {$$ = mk_if($2, $4, $6);}
     | IF expr THEN stmt_lst END IF SEMI                {$$ = mk_if($2, $4, NULL);}
     | WHILE expr LOOP stmt_lst END LOOP SEMI           {$$ = mk_while($2, $4);}
     | IDENTIFIER ASSIGN expr SEMI                      {$$ = mk_assign($1, $3);}
     | GET_LINE LPAREN IDENTIFIER RPAREN SEMI           {$$ = mk_getline($3);}
     | PUT_LINE LPAREN IDENTIFIER RPAREN SEMI           {$$ = mk_putline($3);}
     ;

expr: NUM                         {$$ = mk_numexp($1);}
    | REAL                        {$$ = mk_floatexp($1);}
    | IDENTIFIER                  {$$ = mk_idexp($1);}
    | TRUE                        {$$ = mk_boolexp(1);}
    | FALSE                       {$$ = mk_boolexp(0);}
    | LPAREN expr RPAREN          {$$ = mk_parenexp($2);}
    | expr EQ expr                {$$ = mk_opexp($1, EQop, $3);}
    | expr NEQ expr               {$$ = mk_opexp($1, NEQop, $3);}
    | expr GT expr                {$$ = mk_opexp($1, GTop, $3);}
    | expr LT expr                {$$ = mk_opexp($1, LTop, $3);}
    | expr GE expr                {$$ = mk_opexp($1, GEop, $3);}
    | expr LE expr                {$$ = mk_opexp($1, LEop, $3);}
    | expr AND expr               {$$ = mk_opexp($1, ANDop, $3);}
    | expr OR expr                {$$ = mk_opexp($1, ORop, $3);}
    | expr XOR expr               {$$ = mk_opexp($1, XORop, $3);}
    | NOT expr                    {$$ = mk_unexp(NOTop, $2);}
    | expr PLUS expr              {$$ = mk_opexp($1, PLUSop, $3);}
    | expr MINUS expr             {$$ = mk_opexp($1, MINUSop, $3);}
    | expr TIMES expr             {$$ = mk_opexp($1, TIMESop, $3);}
    | expr DIVIDE expr            {$$ = mk_opexp($1, DIVIDEop, $3);}
    | expr MOD expr               {$$ = mk_opexp($1, MODop, $3);}
    | expr REM expr               {$$ = mk_opexp($1, REMop, $3);}
    | expr POWER expr             {$$ = mk_opexp($1, POWERop, $3);}
    ;   

%%

void yyerror(char const *msg) {
   printf("parse error: %s\n", msg);
   exit(-1);
}

void printAST(){
    print_stm(root);
}
