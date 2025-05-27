#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "tokens.h"

Token getNextToken(FILE *file);
void tokenize(FILE *file, TokenArray *tokenArray);
//char peekch(FILE *file); // should only be avaliable in the lexer

#endif