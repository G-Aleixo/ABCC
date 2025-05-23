#include <stdlib.h>
#include <string.h>

#include "ast.h"

ASTNode *createConstNode(int value) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_CONSTANT;
    node->constNode.value = value;
    return node;
}
ASTNode *createReturnNode(ASTExp *expression) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->returnNode.expression = expression;
    return node;
}
ASTNode *createFuncDeclareNode(const char *name, ASTReturn *statement) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECLARE;
    strncpy(node->funcDeclareNode.name, name, MAX_LEXEME_LENGTH);
    node->funcDeclareNode.statement = statement;
    return node;
}
ASTNode *createProgNode(ASTFuncDeclare *funcDeclare) {
    ASTNode *node = (ASTNode *) malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->progNode.func_declare = funcDeclare;
    return node;
}

void freeAST(ASTNode *node) {
    if (node) {
        free(node);
    }
}