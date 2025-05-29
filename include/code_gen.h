#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <ast.h>
#include <stdio.h>
#include <stdlib.h>

int generate(ASTNode *ast, FILE *output_file);

#endif