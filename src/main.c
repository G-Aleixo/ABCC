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

int main(int argc, char* argv[]) {

    // check if the file is given
    if (argc < 2) {
        puts("Please provide a file to compile.");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

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