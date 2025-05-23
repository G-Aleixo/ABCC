#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"
#include "parser.h"

void printToken(Token token) {
    printf("Lexeme: %-10s Type: %d\n", token.lexeme, token.type);
}

int main() {
    FILE* file = fopen("test.c", "r");

    if (file == NULL) {
        puts("The file could not be oppened");
        return 1;
    }

    // try to get tokens :)
    TokenArray tokenArray;
    tokenize(file, &tokenArray);

    parse(&tokenArray);

    return 0;
}