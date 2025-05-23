#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "tokens.h"

Token getNextToken(FILE *file);
void tokenize(FILE *file, TokenArray *tokenArray);
char peek(FILE *file);

#endif