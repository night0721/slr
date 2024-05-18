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
            token = malloc(sizeof(Token));
            char *value = malloc(2 * sizeof(char));
            value[0] = current[current_index];
            value[1] = '\0';
            token->value = value;
            token->type = SEPARATOR;
            tokens[tokens_index] = *token;
            tokens_index++;
            printf("FOUND SEMICOLON\n");
        } else if(current[current_index] == '(') {
            token = malloc(sizeof(Token));
            char *value = malloc(2 * sizeof(char));
            value[0] = current[current_index];
            value[1] = '\0';
            token->value = value;
            token->type = SEPARATOR;
            tokens[tokens_index] = *token;
            tokens_index++;
            printf("FOUND OPEN PAREN\n");
        } else if(current[current_index] == ')') {
            token = malloc(sizeof(Token));
            char *value = malloc(2 * sizeof(char));
            value[0] = current[current_index];
            value[1] = '\0';
            token->value = value;
            token->type = SEPARATOR;
            tokens[tokens_index] = *token;
            tokens_index++;
            printf("FOUND CLOSE PAREN\n");
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
        if (token != NULL) {
            print_token(*token);
        }
        current_index++;
    }
    tokens[tokens_index].type = END_OF_TOKENS;
    tokens[tokens_index].value = '\0';
    return tokens;
}

