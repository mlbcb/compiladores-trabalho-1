typedef enum {PLUSop, MINUSop, TIMESop, DIVIDEop, REMop, MODop, POWERop, EQop, NEQop, 
              GTop, LTop, GEop, LEop, ANDop, ORop, XORop
}BinOp;

typedef enum {NOTop
}UnOp;

typedef enum { IDEXP, NUMEXP, FLOATEXP, BOOLEXP, OPEXP, PARENEXP, UNEXP
}ExpType;

struct _Exp {
    ExpType exp_t;     // tag
    union {            // alternatives
        char *ident;   // IDEXP
        int num;       // NUMEXP
        float fnum;    // FLOATEXP
        int bool;      // BOOLEXP
        struct {   
            struct _Exp *left;
            BinOp op;
            struct _Exp *right;
        } opexp;        // OPEXP
        struct {
            UnOp op;
            struct _Exp *right;
        } unexp;         // UNEXP
        struct {
            struct _Exp *inside;
        } parenexp;      //PARENEXP
    } fields;
};
typedef struct _Exp *Exp;


typedef enum { ASSIGNSTM, COMPOUNDSTM, IFSTM, WHILESTM, PROCEDSTM, GETLINESTM, PUTLINESTM
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
            struct _Stm *then_child;
            struct _Stm *else_child;
        }ifstm;         //IFSTM
        struct {
            Exp cond;
            struct _Stm *child;
        } whilestm;      //WHILESTM
        struct {
            char *input;
        } getlinestm;    //GETLINESTM
        struct {
            char *ouput;
        } putlinestm;    //PUTLINESTM
        struct {
            struct _Stm *stmt;
        } procedstm;      //PROCEDSTM
    } fields;
};
typedef struct _Stm *Stm;


extern Stm mk_compound(Stm, Stm);
extern Stm mk_assign(char *, Exp);
extern Stm mk_if(Exp, Stm, Stm);
extern Stm mk_while(Exp, Stm);
extern Stm mk_getline(char *);
extern Stm mk_putline(char *);
extern Stm mk_proced(Stm);

extern Exp mk_opexp(Exp, BinOp, Exp);
extern Exp mk_unexp(UnOp, Exp);
extern Exp mk_numexp(int);
extern Exp mk_idexp(char *);
extern Exp mk_boolexp(int);
extern Exp mk_floatexp(float);
extern Exp mk_parenexp(Exp);

extern void print_exp(Exp);
extern void print_stm(Stm);
