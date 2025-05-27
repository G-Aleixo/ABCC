#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "ast.h"

int arrayIndex = 0;

Token *next(TokenArray *tokenArray) {
    if (arrayIndex < tokenArray->size) {
        return &tokenArray->tokens[arrayIndex++];
    }
    return NULL; // No more tokens
}

Token *peekToken(TokenArray *tokenArray) {
    if (arrayIndex < tokenArray->size) {
        return &tokenArray->tokens[arrayIndex];
    }
    return NULL; // No more tokens
}

ASTNode *parse(TokenArray *tokenArray) {
    Token *token;


    fprintf(stderr, "ERORR: parse function not implemented yet\n");
    return NULL;
}

ASTNode *parse_statement(TokenArray *tokenArray) {
    Token *token = next(tokenArray);
    if (token == NULL) {
        return NULL; // No more tokens
    };

    ASTNode *node = NULL;

    switch (token->type) {
        case KEYWORD:
            if (strcmp(token->lexeme, "return") != 0) {
                fprintf(stderr, "Expected 'return' keyword, got '%s'\n", token->lexeme);
                exit(EXIT_FAILURE);
            }
            Token *nextToken = peekToken(tokenArray);
            if (nextToken != NULL && nextToken->type == NUMBER) {
                next(tokenArray);
                ASTNode *expression = createExpNode(createConstNode(nextToken->lexeme, CONST_NUMBER));
                node = createReturnNode(expression);
            }
            break;
        
        default:
            fprintf(stderr, "Unexpected token type: %d\n", token->type);
            exit(EXIT_FAILURE);
    }

    return node;
}

ASTNode *parse_func(TokenArray *tokenArray) {
    Token *nextToken;

    Token *token = next(tokenArray);
    if (token == NULL) {
        return NULL; // Not a function declaration
    }

    if (token->type != KEYWORD) {
        fprintf(stderr, "Expected function declaration keyword, got '%s'\n", token->lexeme);
        exit(EXIT_FAILURE);
    }

    if (strcmp(token->lexeme, "int") != 0) {
        fprintf(stderr, "Expected 'int' keyword, got '%s'\n", token->lexeme);
        exit(EXIT_FAILURE);
    }

    if (peekToken(tokenArray) == NULL || peekToken(tokenArray)->type != IDENTIFIER) {
        fprintf(stderr, "Expected function name after 'int', got '%s'\n", token->lexeme);
        exit(EXIT_FAILURE);
    }

    Token *funcNameToken = next(tokenArray);

    ASTNode *funcNode = createFuncDeclareNode(funcNameToken->lexeme, NULL);

    nextToken = next(tokenArray);

    if (nextToken == NULL || nextToken->type != LPARENTHESIS) {
        fprintf(stderr, "Expected '(' after function name, got '%s'\n", nextToken->lexeme);
        exit(EXIT_FAILURE);
    }

    nextToken = next(tokenArray);

    if (nextToken == NULL || nextToken->type != RPARENTHESIS) {
        fprintf(stderr, "Expected ')' after function parameters, got '%s'\n", nextToken->lexeme);
        exit(EXIT_FAILURE);
    }

    nextToken = next(tokenArray);

    if (nextToken == NULL || nextToken->type != LBRACE) {
        fprintf(stderr, "Expected '{' after function declaration, got '%s'\n", nextToken->lexeme);
        exit(EXIT_FAILURE);
    }

    ASTNode *statement = parse_statement(tokenArray);

    if (statement == NULL) {
        fprintf(stderr, "Expected a statement inside function body\n");
        exit(EXIT_FAILURE);
    }

    if (nextToken == NULL || nextToken->type != RBRACE) {
        fprintf(stderr, "Expected '}' at the end of function body, got '%s'\n", nextToken->lexeme);
        exit(EXIT_FAILURE);
    }

    funcNode->data.funcDeclareNode.statement = statement;

    return funcNode;
}