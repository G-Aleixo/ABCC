#ifndef PARSER_H
#define PARSER_H

#include "tokens.h"
#include "ast.h"

ASTNode *parse(TokenArray *tokenArray);

//ASTNode *parseExpression(TokenArray *tokenArray, int pos);

#endif