#include <stdio.h>
#include <stdlib.h>

#include "code_gen.h"
#include "ast.h"

int generate_expression(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Invalid AST node or output file.\n");
        return -1;
    }

    // generate code for an expression
    fprintf(output_file, "  movl $%s, %%eax\n", node->data.expNode.expression->data.constNode.value);

    return 0;
}
int generate_return_code(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Invalid AST node or output file.\n");
        return -1;
    }

    generate_expression(node->data.returnNode.expression, output_file);

    fprintf(output_file, "  ret");

    return 0;
}

int generate_code(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Error: Invalid AST node or output file.\n");
        return -1;
    }

    // generate code for a single function declaration
    if (node->type == NODE_PROGRAM) {
        ASTNode *func_declare = node->data.progNode.func_declare;
        char *func_name = func_declare->data.funcDeclareNode.name;
        fprintf(output_file, ".globl %s\n", func_name);

        fprintf(output_file, "%s:\n", func_name);

        // Generate code for the function body
        if (func_declare->data.funcDeclareNode.statement != NULL) {
            generate_return_code(func_declare->data.funcDeclareNode.statement, output_file);
        } else {
            fprintf(output_file, "  ret\n");
        }
    }


    return 0;
}