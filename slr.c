#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

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
		return 1;
    }
    FILE *file = fopen(argv[1], "r");
	if (!file) {
		perror("fopen");
		return 1;
	}
    long long length = get_file_length(file);
    char *buf = malloc(length * sizeof(char));
    fread(buf, 1, length, file);
    fclose(file);
    buf[length + 1] = '\0';
    Token *tokens = lexer(buf);
	for(size_t i = 0; tokens[i].type != END_OF_TOKENS; i++){
		print_token(tokens[i]);
	}
}

/* https://github.com/CobbCoding1/unnamed-lang/commit/10ecba484a0b47110c19b2604500c9ae49f84c52 */
