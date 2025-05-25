#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

ASTNode *createConstNode(int value) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_CONSTANT;
    node->data.constNode.value = value;
    return node;
}

ASTNode *createExpNode(ASTNode *constNode) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_EXPRESSION;
    node->data.expNode.const_expression = constNode;
    return node;
}

ASTNode *createReturnNode(ASTNode *expression) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.returnNode.expression = expression;
    return node;
}
ASTNode *createFuncDeclareNode(const char *name, ASTNode *statement) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECLARE;
    strncpy(node->data.funcDeclareNode.name, name, MAX_LEXEME_LENGTH);
    node->data.funcDeclareNode.statement = statement;
    return node;
}
ASTNode *createProgNode(ASTNode *funcDeclare) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.progNode.func_declare = funcDeclare;
    return node;
}

void freeAST(ASTNode *node) {
    if (node) {
        free(node);
    }
}

void printAST(ASTNode *node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    

    switch (node->type) {
        case NODE_CONSTANT:
            printf("Constant: %d\n", node->data.constNode.value);
            break;
        case NODE_RETURN:
            printf("Return:\n");
            printAST(node->data.returnNode.expression, depth + 1);
            break;
        case NODE_FUNC_DECLARE:
            printf("Function Declaration: %s\n", node->data.funcDeclareNode.name);
            printAST(node->data.funcDeclareNode.statement, depth + 1);
            break;
        case NODE_PROGRAM:
            printf("Program:\n");
            printAST(node->data.progNode.func_declare, depth + 1);
            break;
        default:
            printf("Unknown node type\n");
    }
}