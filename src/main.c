#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "code_gen.h"

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

    for (int i = 0; i < tokenArray.size; i++) {
        printToken(tokenArray.tokens[i]); //
    }

    ASTNode *program = parse(&tokenArray);

    // file is no longer needed
    fclose(file);

    printAST(program);

    FILE* outputFile = fopen("output.s", "w");

    if (outputFile == NULL) {
        puts("Could not open output file.");
        return 1;
    }

    generate(program, outputFile);

    fclose(outputFile);

    return 0;
}