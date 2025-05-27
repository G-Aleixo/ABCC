#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <ast.h>
#include <stdio.h>

int generate_code(ASTNode *ast, FILE *output_file);

#endif