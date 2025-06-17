#include <stdio.h>
#include <stdlib.h>

#include "code_gen.h"
#include "ast.h"

void print_spaces(FILE *output_file, int level) {
    for (int i = 0; i < level; i++) {
        fprintf(output_file, "  ");
    }
}

int generate_unary_op(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Parser Error: Invalid AST node or output file.\n");
        return -1;
    }

    // generate code for a unary operation
    if (node->type != NODE_UNARY_OP) {
        fprintf(stderr, "Parser Error: Expected a unary operation node.\n");
        return -1;
    }

    // generate code for inside expression
    if (node->data.unaryOpNode.expression == NULL) {
        fprintf(stderr, "Parser Error: Expected expression for unary operator.\n");
        return -1;
    }

    switch (node->data.unaryOpNode.expression->type) {
        case NODE_CONSTANT:
            // move the constant value into a0 register
            fprintf(output_file, "  li a0, %s\n", node->data.unaryOpNode.expression->data.constNode.value);
            break;
        case NODE_UNARY_OP:
            // generate code for the inside operation
            if (generate_unary_op(node->data.unaryOpNode.expression, output_file) != 0) {
                fprintf(stderr, "Parser Error: Failed to generate code for inner unary operation.\n");
                return -1;
            }
            break;
        default:
            fprintf(stderr, "Parser Error: Unsupported expression type for unary operation.\n");
            return -1;
    }

    print_spaces(output_file, 1);
    // generate code to execute the operation
    switch (node->data.unaryOpNode.operator) {
        case '-':
            fprintf(output_file, "neg a0, a0\n");
            break;
        case '~':
            fprintf(output_file, "not a0, a0\n");
            break;
        // case '!':
        //     add support later
        default:
            fprintf(stderr, "Parser Error: Unsupported unary operator '%c'.\n", node->data.unaryOpNode.operator);
            return -1;
    }

    return 0;
}

int generate_expression(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Parser Error: Invalid AST node or output file.\n");
        return -1;
    }

    // generate code for an expression
    
    if (node->type != NODE_EXPRESSION) {
        fprintf(stderr, "Parser Error: Expected an expression node.\n");
        return -1;
    }

    switch (node->data.expNode.expression->type) {
        case NODE_CONSTANT:
            if (node->data.expNode.expression->data.constNode.value == NULL) {
                fprintf(stderr, "Parser Error: Constant value is NULL.\n");
                return -1;
            }
            // Move the constant value into a0 register
            fprintf(output_file, "  li a0, %s\n", node->data.expNode.expression->data.constNode.value);

            break;
        case NODE_UNARY_OP:
            // Generate code for unary operation
            if (generate_unary_op(node->data.expNode.expression, output_file) != 0) {
                fprintf(stderr, "Parser Error: Failed to generate code for unary operation.\n");
                return -1;
            }
            break;
        default:
            break;
    }
    
    return 0;
}
int generate_return_code(ASTNode *node, FILE *output_file, int level) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Parser Error: Invalid AST node or output file.\n");
        return -1;
    }

    generate_expression(node->data.returnNode.expression, output_file);
    
    print_spaces(output_file, level);
    fprintf(output_file, "ret");

    return 0;
}

int generate(ASTNode *node, FILE *output_file) {
    if (node == NULL || output_file == NULL) {
        fprintf(stderr, "Parser Error: Invalid AST node or output file.\n");
        return -1;
    }

    puts("Starting code generation...");

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
            int ret = generate_return_code(func_declare->data.funcDeclareNode.statement, output_file, 1);

            if (ret != 0) {
                fprintf(stderr, "Parser Error: Failed to generate code for function body.\n");
                // close file
                fclose(output_file);
                return -1;
            }

        } else {
            print_spaces(output_file, 1);
            fprintf(output_file, "ret\n");
        }
    }

    puts("Code generation completed successfully.");

    return 0;
}