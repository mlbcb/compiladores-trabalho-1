/* Functions for building Abstract Syntax Trees (AST)*/
#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

/* Construct expressions*/
/*INT*/
Exp mk_numexp(int num){
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = NUMEXP;
    ptr->fields.num = num;
    return ptr;
}

/*FLOAT*/
Exp mk_floatexp(float num){
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = FLOATEXP;
    ptr->fields.fnum = num;
    return ptr;
}

/*ID*/
Exp mk_idexp(char *ident){
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = IDEXP;
    ptr->fields.ident = ident;
    return ptr;
}

/*BOOLEAN*/
Exp mk_boolexp(int bool) {
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = BOOLEXP;
    ptr->fields.bool = bool;
    return ptr;
}

/*FLOAT*/
Exp mk_floatexp(float num) {
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = FLOATEXP;
    ptr->fields.fnum = num;
    return ptr;
}

/*OP*/
Exp mk_opexp(Exp left, BinOp op, Exp right) {
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = OPEXP;
    ptr->fields.opexp.left = left;
    ptr->fields.opexp.right = right;
    ptr->fields.opexp.op = op;
    return ptr;
}

Exp mk_parenexp(Exp inside) {
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = PARENEXP;
    ptr->fields.parenexp.inside = inside;
    return ptr;
}

/* Construct statements*/
Stm mk_assign(char *ident, Exp exp) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = ASSIGNSTM;
    ptr->fields.assign.ident = ident;
    ptr->fields.assign.exp = exp;
    return ptr;
}


Stm mk_compound(Stm fst, Stm snd) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = COMPOUNDSTM;
    ptr->fields.compound.fst = fst;
    ptr->fields.compound.snd = snd;
    return ptr;
}

Stm mk_if(Exp cond, Stm then_child, Stm else_child) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = IFSTM;
    ptr->fields.ifstm.cond = cond;
    ptr->fields.ifstm.then_child = then_child;
    ptr->fields.ifstm.else_child = else_child;
    return ptr;
}

Stm mk_while(Exp cond, Stm child) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = WHILESTM;
    ptr->fields.whilestm.cond = cond;
    ptr->fields.whilestm.child = child;
    return ptr;
}

Stm mk_proced(Stm stmt) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = PROCEDSTM;
    ptr->fields.procedstm.stmt = stmt;
    return ptr;
}


/* Pretty-Print an expression*/
void print_op(BinOp op) {
    switch(op) {
        case PLUS:
            printf(" + ");
            break;
        case MINUS:
            printf(" - ");
            break;
        case TIMES:
            printf(" * ");
            break;
        case DIVISION:
            printf(" / ");
            break;
        case REM:
            printf(" rem ");
            break;
        case MOD:
            printf(" mod ");
            break;
        case POWER:
            printf(" ** ");
            break;
        case EQUAL_TO:
            printf(" = ");
            break;    
        case DIFFERENT_THAN:
            printf(" /= ");
            break;    
        case GREATER_THAN:
            printf(" > ");
            break;
        case LESS_THAN:
            printf(" < ");
            break;
        case EQUAL_OR_GREATER:
            printf(" >= ");
            break;    
        case EQUAL_OR_LESS:
            printf(" <= ");
            break;    
        case AND:
            printf(" and ");
            break;
        case OR:
            printf(" or ");
            break;
        case XOR:
            printf(" xor ");
            break;
    }              
}

void print_exp(Exp ptr) {
    switch (ptr->exp_t) {
        case NUMEXP:
            printf("%d", ptr->fields.num);
            break;
        case IDEXP:
            printf("%s", ptr->fields.ident);
            break;
        case OPEXP:
            print_exp(ptr->fields.opexp.left);
            print_op(ptr->fields.opexp.op);
            print_exp(ptr->fields.opexp.right);
            break;
        case BOOLEXP:
            if(ptr->fields.bool)
                printf("TRUE");
            else
                printf("FALSE");
            break;
        case FLOATEXP:
            printf("%f", ptr->fields.bool);
            break;
        case PARENEXP:
            printf("(");
            print_exp(ptr->fields.parenexp.inside);
            printf(")");
            break;
    }
}

/* Pretty-print a statement*/
void print_stm(Stm ptr) {
    switch(ptr->stm_t) {
        case ASSIGNSTM:
            printf("%s", ptr->fields.assign.ident);
            printf("=");
            print_exp(ptr->fields.assign.exp);
            printf("; ");
            break;
        case COMPOUNDSTM:
            print_stm(ptr->fields.compound.fst);
            print_stm(ptr->fields.compound.snd);
            break;
        case IFSTM:
            printf("IF");
            print_stm(ptr->fields.ifstm.cond);
            printf("THEN");
            print_stm(ptr->fields.ifstm.then_child);
            if(ptr->fields.ifstm.else_child != NULL){
                printf("ELSE");
                print_stm(ptr->fields.ifstm.else_child);
            }
            printf("END IF;");
            break;
        case WHILESTM:
            printf("WHILE");
            print_stm(ptr->fields.whilestm.cond);
            printf("LOOP");
            print_stm(ptr->fields.whilestm.child);
            printf("END LOOP;");
            break;
        case PROCEDSTM:
            printf("PROCEDURE MAIN IS BEGIN");
            print_stm(ptr->fields.procedstm.stmt);
            printf("END MAIN;");
            break;
    }
}

