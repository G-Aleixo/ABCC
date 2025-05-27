#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "ast.h"

Token *next(TokenArray *tokenArray) {
    if (tokenArray->index < tokenArray->size) {
        return &tokenArray->tokens[tokenArray->index++];
    }
    return NULL; // No more tokens
}

Token *peekToken(TokenArray *tokenArray) {
    if (tokenArray->index < tokenArray->size) {
        return &tokenArray->tokens[tokenArray->index];
    }
    return NULL; // No more tokens
}


ASTNode *parse_statement(TokenArray *tokenArray) {
    Token *token = next(tokenArray);
    if (token == NULL) {
        fprintf(stderr, "Error: No tokens available for parsing statement\n");
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
                token = next(tokenArray);
                if (token == NULL || token->type != SEMICOLON) {
                    fprintf(stderr, "Expected ';' after return value, got '%s'\n", token->lexeme);
                    exit(EXIT_FAILURE);
                }
                ASTNode *expression = createExpNode(createConstNode(nextToken->lexeme, CONST_NUMBER));
                node = createReturnNode(expression);
            } else {
                fprintf(stderr, "Expected a return value after 'return', got '%s'\n", nextToken ? nextToken->lexeme : "EOF");
                exit(EXIT_FAILURE);
            }
            break;
        
        default:
            fprintf(stderr, "Unexpected token: %s\n", token->lexeme);
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
        printf("TOKEN TYPE: %d\n", peekToken(tokenArray)->type);
        fprintf(stderr, "Expected function name after 'int', got '%s'\n", peekToken(tokenArray)->lexeme);
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

    nextToken = next(tokenArray);

    if (nextToken == NULL || nextToken->type != RBRACE) {
        fprintf(stderr, "Expected '}' at the end of function body, got '%s'\n", nextToken->lexeme);
        exit(EXIT_FAILURE);
    }

    funcNode->data.funcDeclareNode.statement = statement;

    return funcNode;
}

ASTNode *parse(TokenArray *tokenArray) {
    if (tokenArray == NULL || tokenArray->size == 0) {
        fprintf(stderr, "Error: Token array is empty or NULL\n");
        return NULL;
    }

    ASTNode *ast = createProgNode(NULL); // Create an empty program node

    if (ast == NULL) {
        fprintf(stderr, "Error: Failed to create AST root node\n");
        return NULL;
    }

    // assume anything that isn't inside a function and starts with a keyword is a function declaration
    tokenArray->index = 0; // Reset index to start parsing from the beginning

    for (int i = 0; i < tokenArray->size; i++) {
        if (tokenArray->tokens[i].type == KEYWORD && strcmp(tokenArray->tokens[i].lexeme, "int") == 0) {
            // Found a function declaration
            ASTNode *funcNode = parse_func(tokenArray);
            if (funcNode == NULL) {
                fprintf(stderr, "Error parsing function declaration\n");
                return NULL;
            }
            // Add the function node to the AST
            ast->data.progNode.func_declare = funcNode;
        }
    }

    return ast;
}