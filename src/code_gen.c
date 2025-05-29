#include <stdio.h>
#include <stdlib.h>

#include "code_gen.h"
#include "ast.h"

void print_spaces(FILE *output_file, int level) {
    for (int i = 0; i < level; i++) {
        fprintf(output_file, "  ");
    }
}

int generate_expression(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Invalid AST node or output file.\n");
        return -1;
    }

    // generate code for an expression
    fprintf(output_file, "  li a0, %s\n", node->data.expNode.expression->data.constNode.value);

    return 0;
}
int generate_return_code(ASTNode *node, FILE *output_file, int level) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Invalid AST node or output file.\n");
        return -1;
    }

    generate_expression(node->data.returnNode.expression, output_file);

    print_spaces(output_file, level);
    fprintf(output_file, "ret");

    return 0;
}

int generate(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Invalid AST node or output file.\n");
        return -1;
    }

    // generate code for a single function declaration
    if (node->type == NODE_PROGRAM) {
        ASTNode *func_declare = node->data.progNode.func_declare;
        char *func_name = func_declare->data.funcDeclareNode.name;

        // expose the function declared and start to the linker
        fprintf(output_file, ".section .text\n");
        fprintf(output_file, "  .globl %s\n", func_name);
        fprintf(output_file, "  .globl _start\n");

        fprintf(output_file, "_start:\n");
        fprintf(output_file, "  jal ra, %s\n", func_name);

        fprintf(output_file, "%s:\n", func_name);

        // Generate code for the function body
        if (func_declare->data.funcDeclareNode.statement != NULL) {
            generate_return_code(func_declare->data.funcDeclareNode.statement, output_file, 1);
        } else {
            print_spaces(output_file, 1);
            fprintf(output_file, "ret\n");
        }
    }


    return 0;
}