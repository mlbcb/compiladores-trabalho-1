/* Functions for building Abstract Syntax Trees (AST)*/
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

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

/*IDENTIFIER*/
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

/*OP*/
Exp mk_opexp(Exp left, BinOp op, Exp right) {
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = OPEXP;
    ptr->fields.opexp.left = left;
    ptr->fields.opexp.right = right;
    ptr->fields.opexp.op = op;
    return ptr;
}

/*NOT*/
Exp mk_unexp(UnOp op, Exp right) {
    Exp ptr = malloc(sizeof(struct _Exp));
    ptr->exp_t = UNEXP;
    ptr->fields.unexp.op = op;
    ptr->fields.unexp.right = right;
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

Stm mk_putline(char *output) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = PUTLINESTM;
    ptr->fields.putlinestm.ouput = output;
    return ptr;
}

Stm mk_getline(char *input) {
    Stm ptr = malloc(sizeof(struct _Stm));
    ptr->stm_t = GETLINESTM;
    ptr->fields.getlinestm.input = input;
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
        case PLUSop:
            printf(" + ");
            break;
        case MINUSop:
            printf(" - ");
            break;
        case TIMESop:
            printf(" * ");
            break;
        case DIVIDEop:
            printf(" / ");
            break;
        case REMop:
            printf(" rem ");
            break;
        case MODop:
            printf(" mod ");
            break;
        case POWERop:
            printf(" ** ");
            break;
        case EQop:
            printf(" = ");
            break;    
        case NEQop:
            printf(" /= ");
            break;    
        case GTop:
            printf(" > ");
            break;
        case LTop:
            printf(" < ");
            break;
        case GEop:
            printf(" >= ");
            break;    
        case LEop:
            printf(" <= ");
            break;    
        case ANDop:
            printf(" and ");
            break;
        case ORop:
            printf(" or ");
            break;
        case XORop:
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
        case UNEXP:
            print_op(ptr->fields.unexp.op);
            print_exp(ptr->fields.unexp.right);
            break;
        case BOOLEXP:
            if(ptr->fields.bool)
                printf("TRUE");
            else
                printf("FALSE");
            break;
        case FLOATEXP:
            printf("%f", ptr->fields.fnum);
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
            printf(" := ");
            print_exp(ptr->fields.assign.exp);     
            printf(";\n");
            break;
        case COMPOUNDSTM:
            print_stm(ptr->fields.compound.fst);
            print_stm(ptr->fields.compound.snd);
            break;
        case IFSTM:
            printf("IF ");
            print_exp(ptr->fields.ifstm.cond);
            printf(" THEN ");
            print_stm(ptr->fields.ifstm.then_child);
            if(ptr->fields.ifstm.else_child != NULL){
                printf("ELSE ");
                print_stm(ptr->fields.ifstm.else_child);
            }
            printf("END IF; \n");
            break;
        case WHILESTM:
            printf("WHILE ");
            print_exp(ptr->fields.whilestm.cond);
            printf(" LOOP ");
            print_stm(ptr->fields.whilestm.child);
            printf("END LOOP; \n");
            break;
        case PROCEDSTM:
            printf("PROCEDURE MAIN IS BEGIN\n");
            print_stm(ptr->fields.procedstm.stmt);
            printf("END MAIN; \n");
            break;
        case PUTLINESTM:
            printf("PUT_LINE(");
            printf("%s", ptr->fields.putlinestm.ouput);
            printf(");\n");
            break;
        case GETLINESTM:
            printf("GET_LINE(");
            printf("%s", ptr->fields.getlinestm.input);
            printf(");\n");
            break;
    }
}

