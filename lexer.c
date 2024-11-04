#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

Token *lexer(char *buf)
{
    char *current = strdup(buf);
    int current_index = 0, tokens_index = 0;

    Token *tokens = malloc(sizeof(Token) * 1024);
    while(current[current_index] != '\0') {
        Token *token = NULL;
        if(current[current_index] == ';') {
			token = generate_separator(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if(current[current_index] == '(') {
            token = generate_separator(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if(current[current_index] == ')') {
			token = generate_separator(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
        } else if(isdigit(current[current_index])) {
            token = generate_number(current, &current_index); 
            tokens[tokens_index] = *token;
            tokens_index++;
            current_index--;
        } else if(isalpha(current[current_index])) {
            token = generate_keyword(current, &current_index);
            tokens[tokens_index] = *token;
            tokens_index++;
            current_index--;
        }
        current_index++;
    }
    tokens[tokens_index].type = END_OF_TOKENS;
    tokens[tokens_index].value = NULL;
    return tokens;
}

void print_token(Token token)
{
  printf("Token Value: \"");
  for (int i = 0; token.value[i] != '\0'; i++) {
    printf("%c", token.value[i]);
  }
  printf("\"\nToken Type: ");
  switch (token.type) {
      case INT:
          printf("int\n");
          break;
      case KEYWORD:
          printf("Keyword\n");
          break;
      case SEPARATOR:
          printf("Separator\n");
          break;
	  case END_OF_TOKENS:
		  printf("End of Tokens\n");
		  break;
  }
}

Token *generate_separator(char *current, int *current_index)
{
  Token *token = malloc(sizeof(Token));
  token->value = malloc(sizeof(char) * 2);
  token->value[0] = current[*current_index];
  token->value[1] = '\0';
  token->type = SEPARATOR;
  return token;
}

Token *generate_number(char *current, int *current_index)
{
    Token *token = malloc(sizeof(Token));
    token->type = INT;
    char *value = malloc(8 * sizeof(char));
    int value_index = 0;
    while(isdigit(current[*current_index]) && current[*current_index] != '\0') {
        value[value_index] = current[*current_index];
        value_index++;
        (*current_index)++;
    }
    value[value_index] = '\0';
    token->value = value;
    return token;
}

Token *generate_keyword(char *current, int *current_index)
{
    Token *token = malloc(sizeof(Token));
    char *keyword = malloc(8 * sizeof(char));
    int keyword_index = 0;
    while(isalpha(current[*current_index]) && current[*current_index] != '\0') {
        keyword[keyword_index] = current[*current_index];
        keyword_index++;
        (*current_index)++;
    }
    keyword[keyword_index] = '\0';
    if(strcmp(keyword, "exit") == 0) {
        printf("TYPE EXIT\n");
        token->type = KEYWORD;
    }
    token->type = KEYWORD;
    token->value = keyword;
    return token;
}
