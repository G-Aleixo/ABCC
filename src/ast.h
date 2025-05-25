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

struct ASTNode;

typedef struct {
    int value;
} ASTConst;
typedef struct {
    ASTNode *const_expression;
} ASTExp;
typedef struct {
    ASTNode *expression;
} ASTReturn;
typedef struct {
    char name[MAX_LEXEME_LENGTH];
    ASTNode *statement;
} ASTFuncDeclare;
typedef struct {
    ASTNode *func_declare;
} ASTProg;

typedef struct {
    ASTNodeType type;
    union {
        ASTConst constNode;
        ASTExp expNode;
        ASTReturn returnNode;
        ASTFuncDeclare funcDeclareNode;
        ASTProg progNode;
    } data;
    
} ASTNode;

ASTNode *createConstNode(int value);
ASTNode *createExpNode(ASTNode *expression);
ASTNode *createReturnNode(ASTNode *expression);
ASTNode *createFuncDeclareNode(const char *name, ASTNode *statement);
ASTNode *createProgNode(ASTNode *funcDeclare);

void freeAST(ASTNode *node);
void printAST(ASTNode *node, int level);

#endif