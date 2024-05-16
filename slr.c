#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "slr.h"
#include "lexer.h"

void print_token(Token token)
{
  printf("Token Value: ");
  for (int i = 0; token.value[i] != '\0'; i++) {
    printf("%c", token.value[i]);
  }
  printf("\nToken Type: ");
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
  }
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

long long get_file_length(FILE *file)
{
    fseeko(file, 0, SEEK_END);
    long long length = ftello(file);
    fseeko(file, 0, SEEK_SET);
    return length;
}


int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "\033[1;37mslr:\033[0m \033[1;31mfatal error:\033[0m no input files\ninterpretation termined.\n");
        exit(1);
    }
    FILE *file = fopen(argv[1], "r");
    long long length = get_file_length(file);
    char *buf = malloc(length * sizeof(char));
    fread(buf, 1, length, file);
    fclose(file);
    buf[length + 1] = '\0';
    Token *tokens = lexer(buf);
}
