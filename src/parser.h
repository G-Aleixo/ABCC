#ifndef PARSER_H
#define PARSER_H

#include "tokens.h"
#include "ast.h"

ASTNode *parse(TokenArray *tokenArray);

#endif