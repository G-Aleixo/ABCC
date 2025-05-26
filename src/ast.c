#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"


ASTNode *createConstNode(char* value, ASTConstType type) {
    ASTNode *node= (ASTNode *) malloc(sizeof(ASTNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_CONSTANT;
    node->data.constNode.type = type;
    
    node->data.constNode.value = (char *) malloc(strlen(value) + 1);

    if (node->data.constNode.value == NULL) {
        free(node);
        return NULL;
    }

    strcmp(node->data.constNode.value, value);

    return node;
}

ASTNode *createExpNode(ASTNode *value) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_EXPRESSION;
    node->data.expNode.expression = value;

    return node;
}
ASTNode *createReturnNode(ASTNode *expression) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_RETURN;
    node->data.returnNode.expression = expression;

    return node;
}
ASTNode *createFuncDeclareNode(const char *name, ASTNode *statement) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_FUNC_DECLARE;
    strncpy(node->data.funcDeclareNode.name, name, MAX_LEXEME_LENGTH - 1);
    node->data.funcDeclareNode.statement = statement;

    return node;
}
ASTNode *createProgNode(ASTNode *funcDeclare) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = NODE_PROGRAM;
    node->data.progNode.func_declare = funcDeclare;

    return node;
}

void freeAST(ASTNode *node) {
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case NODE_CONSTANT:
            // No additional data to free
            break;
        case NODE_EXPRESSION:
            freeAST(node->data.expNode.expression);
            break;
        case NODE_RETURN:
            freeAST(node->data.returnNode.expression);
            break;
        case NODE_FUNC_DECLARE:
            freeAST(node->data.funcDeclareNode.statement);
            break;
        case NODE_PROGRAM:
            freeAST(node->data.progNode.func_declare);
            break;
    }

    free(node);
}
void printAST(ASTNode *node) {
    fprintf(stderr, "ERROR: printAST not implemented\n");
}
void printAST_(ASTNode *node, int level) {

}