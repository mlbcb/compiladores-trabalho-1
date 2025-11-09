#ifndef TOKENS_H
#define TOKENS_H

// Definições dos tokens para o lexer para Ada
typedef enum {
  PROCEDURE, MAIN, IS, BEGIN_TOKEN, END, IF, THEN, ELSE, WHILE, LOOP,
  PUT_LINE, GET_LINE, AND, OR, NOT, XOR,
  NUM, REAL, INTEGER, ID, TRUE, FALSE,
  ASSIGN, EQUAL_TO, DIFFERENT_THAN, EQUAL_OR_GREATER, EQUAL_OR_LESS, GREATER_THAN, LESS_THAN,
  PLUS, MINUS, TIMES, DIVISION, MOD, POWER, REM,
  LPAREN, RPAREN, SEMICOLON, COLON, DOT, COMMA,
  END_OF_FILE
} TokenType;

/* União para os valores dos tokens */
typedef union {
  int ival;
  float fval;
  int bval;      // true/false
  char *text;
} TokenValue;

// Opcional para Bison
typedef TokenValue YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

#endif /* TOKENS_H */