#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"

void fail(int code) {
    puts("Failed to parse!");
    exit(code);
}

ASTNode *parse(TokenArray *tokenArray) {
    puts("Starting to parse tokens...");

    for (int i = 0; i < tokenArray->count; i++) {
        printf("Lexeme: %-10s Type: %d\n", tokenArray->tokens[i].lexeme, tokenArray->tokens[i].type);
    }
}

ASTNode *parseStatement(TokenArray *tokenArray, int pos) {
    if ((tokenArray->tokens)[pos++].type != KEYWORD) {
        fail(1);
    }
    if (strcmp((tokenArray->tokens)[pos++].lexeme, "return") != 0) {
        fail(1);
    }

    ASTNode *expr = parseExpression(tokenArray, pos++);

    ASTNode *return_node = createReturnNode(expr);

    ASTNode *program = createProgNode(createFuncDeclareNode("main", return_node));

    return program;
}

ASTNode *parseExpression(TokenArray *tokenArray, int pos) {
    //TODO: add more rules
    if ((tokenArray->tokens)[pos].type != NUMBER) {
        fail(1);
    }
    ASTNode *expr = createExpNode(createConstNode(atoi((tokenArray->tokens)[pos].lexeme)));

    return expr;
}