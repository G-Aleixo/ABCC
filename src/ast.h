#ifndef AST_H
#define AST_H

#include "tokens.h"

typedef enum {
    NODE_PROGRAM,
    NODE_FUNC_DECLARE,
    NODE_DECLARATION,
    NODE_IDENTIFIER,
    NODE_STATEMENT,
    NODE_RETURN,
    NODE_EXPRESSION,
    NODE_CONSTANT,
    NODE_BLOCK,
    NODE_KEYWORD,
} ASTNodeType;

typedef struct {
    int value;
} ASTConst;
typedef struct {
    ASTConst *const_expression;
} ASTExp;
typedef struct {
    ASTExp *expression;
} ASTReturn;
typedef struct {
    char name[MAX_LEXEME_LENGTH];
    ASTReturn *statement;
} ASTFuncDeclare;
typedef struct {
    ASTFuncDeclare *func_declare;
} ASTProg;

typedef struct {
    ASTNodeType type;
    union {
        ASTConst constNode;
        ASTExp expNode;
        ASTReturn returnNode;
        ASTFuncDeclare funcDeclareNode;
        ASTProg progNode;
    };
    
} ASTNode;

ASTNode *createConstNode(int value); 
ASTNode *createReturnNode();
ASTNode *createFuncDeclareNode();
ASTNode *createProgNode();

void freeAST(ASTNode *node);
void printAST(ASTNode *node, int level);

#endif