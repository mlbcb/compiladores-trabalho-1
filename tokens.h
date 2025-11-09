#ifndef TOKENS_H
#define TOKENS_H

// Definições dos tokens para o lexer para Ada
typedef enum {
  PROCEDURE, MAIN, IS, BEGIN_TOKEN, END, IF, THEN, ELSE, WHILE, LOOP,
  PUT_LINE, GET_LINE, AND, OR, NOT, XOR,
  BOOLEAN_LITERAL, INTEGER_LITERAL, IDENTIFIER,
  ASSIGN, EQ, NEQ, LE, GE, LT, GT,
  PLUS, MINUS, TIMES, DIVIDE,
  LPAREN, RPAREN, SEMI, COLON, DOT, COMMA
} TokenType;

//Definir o tipo booleano
typedef enum {
  TRUE = 1, FALSE = 0
} Boolean;

/* União para os valores dos tokens */
typedef union {
  int ival;
  float fval;
  Boolean bval;
  char *text;      // Valor verdadeiro ou falso (BOOLEAN_LITERAL)
} TokenValue;

// Opcional para Bison
typedef TokenValue YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

#endif /* TOKENS_H */