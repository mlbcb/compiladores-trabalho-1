typedef enum {PLUS, MINUS, TIMES, DIVISION, REM, MOD, POWER, EQUAL_TO, DIFFERENT_THAN, 
              GREATER_THAN, LESS_THAN, EQUAL_OR_GREATER, EQUAL_OR_LESS, AND, OR, XOR
}BinOp;

typedef enum { IDEXP, NUMEXP, FLOATEXP, BOOLEXP, OPEXP, PARENEXP
}ExpType;

struct _Exp {
    ExpType exp_t;     // tag
    union {            // alternatives
        char *ident;   // IDEXP
        int num;       // NUMEXP
        float fnum;    // FLOATEXP
        int bool;   // BOOLEXP
        struct {   
            struct _Exp *left;
            BinOp op;
            struct _Exp *right;
        } opexp;        // OPEXP
        struct {
            struct _Exp *inside;
        } parenexp;      //PARENEXP
    } fields;
};
typedef struct _Exp *Exp;


typedef enum { ASSIGNSTM, COMPOUNDSTM, IFSTM, WHILESTM, PROCEDSTM 
}StmType;

struct _Stm {
    StmType stm_t;     // tag
    union {            // alternatives
        struct {
            char *ident;
            Exp exp;
        } assign;        // ASSIGNSTM
        struct {
            struct _Stm *fst;
            struct _Stm *snd;
        } compound;      // COMPOUNDSTM
        struct {
            Exp cond;
            struct _stm *then_child;
            struct _stm *else_child;
        }ifstm;         //IFSTM
        struct {
            Exp cond;
            struct _stm *child;
        } whilestm;      //WHILESTM
        struct {
            struct _stm *stmt;
        } procedstm;      //PROCEDSTM
    } fields;
};
typedef struct _Stm *Stm;

extern Stm root;

extern Stm mk_compound(Stm, Stm);
extern Stm mk_assign(char *, Exp);
extern Stm mk_if(Exp, Stm, Stm);
extern Stm mk_while(Exp, Stm);

extern Exp mk_opexp(Exp, BinOp, Exp);
extern Exp mk_numexp(int);
extern Exp mk_idexp(char *);
extern Exp mk_boolexp(int);
extern Exp mk_floatexp(float);
extern Exp mk_parenexp(Exp);

extern void print_exp(Exp);
extern void print_stm(Stm);
