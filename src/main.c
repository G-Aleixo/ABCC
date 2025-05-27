#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"

void printToken(Token token) {
    printf("Lexeme: %-10s Type: %d\n", token.lexeme, token.type);
}

int main() {
    FILE* file = fopen("test.abcc", "r");

    if (file == NULL) {
        puts("The file could not be oppened");
        return 1;
    }

    // try to get tokens :)
    TokenArray tokenArray;
    tokenize(file, &tokenArray);

    ASTNode *program = parse(&tokenArray);

    printAST(program);

    return 0;
}