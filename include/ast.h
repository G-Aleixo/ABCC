#ifndef AST_H
#define AST_H

#include "tokens.h"


typedef struct ASTNode ASTNode;
typedef enum {
    NODE_PROGRAM,
    NODE_FUNC_DECLARE,
    NODE_STATEMENT,
    NODE_RETURN,
    NODE_EXPRESSION,
    NODE_CONSTANT,
} ASTNodeType;

typedef enum {
    CONST_NUMBER,
    CONST_STRING,
} ASTConstType;

typedef struct {
    ASTConstType type;
    char* value; // Points to string or value idk
} ASTConst;

typedef struct {
    ASTNode *expression;
} ASTExp;

typedef struct {
    ASTNode *expression;
} ASTReturn;

typedef struct {
    ASTNode *statement;
} ASTStatement;

typedef struct {
    char name[MAX_LEXEME_LENGTH];
    ASTNode *statement;
} ASTFuncDeclare;

typedef struct {
    ASTNode *func_declare;
} ASTProg;

struct ASTNode{
    ASTNodeType type;
    union {
        ASTConst constNode;
        ASTExp expNode;
        ASTReturn returnNode;
        ASTStatement statementNode;
        ASTFuncDeclare funcDeclareNode;
        ASTProg progNode;
    } data;
    
};

ASTNode *createConstNode(char* value, ASTConstType type);
ASTNode *createExpNode(ASTNode *value);
ASTNode *createReturnNode(ASTNode *expression);
ASTNode *createStatementNode(ASTNode *statement);
ASTNode *createFuncDeclareNode(const char *name, ASTNode *statement);
ASTNode *createProgNode(ASTNode *funcDeclare);

void freeAST(ASTNode *node);
void printAST(ASTNode *node);

#endif