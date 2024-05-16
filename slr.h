#ifndef SLR_H_
#define SLR_H_

typedef enum {
  INT,
  KEYWORD,
  SEPARATOR,
  END_OF_TOKENS,
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

#endif
