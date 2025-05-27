#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "tokens.h"
#include "lexer.h"

char peekch(FILE* file) {
    char chr = fgetc(file);
    ungetc(chr, file);

    return chr;
}

Token getNextToken(FILE* file) {
    Token token;
    char chr;
    int pos = 0;

    while ((chr = fgetc(file)) != EOF && isspace(chr));

    if (chr == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    if (isalpha(chr)){
        // chr is a letter
        token.lexeme[pos++] = chr;
        while (isalnum(chr = fgetc(file))) {
            // while new character is alphanumeric keep adding to lexeme
            token.lexeme[pos++] = chr;
        } ungetc(chr, file); // put back final non alnum character
        token.lexeme[pos] = '\0';

        // check types now
        if (strcmp(token.lexeme, "int") == 0 ||
            strcmp(token.lexeme, "return") == 0) {
            token.type = KEYWORD;
        } else {
            // doesn't fit any special identifiers
            token.type = IDENTIFIER;
        }
    } else if (isdigit(chr)) {
        // token is a number
        token.lexeme[pos++] = chr;
        while (isdigit(chr = fgetc(file))) {
            token.lexeme[pos++] = chr;
        } ungetc(chr, file); // put back final non digit character

        token.lexeme[pos] = '\0';
        token.type = NUMBER;
    } else {
        // should be punctuation
        //TODO: add checks later
        token.lexeme[0] = chr;
        token.lexeme[1] = '\0';

        switch (chr) {
            case '(': token.type = LPARENTHESIS; break;
            case ')': token.type = RPARENTHESIS; break;
            case '{': token.type = LBRACE; break;
            case '}': token.type = RBRACE; break;
            case ';': token.type = SEMICOLON; break;
            default: token.type = UNKNOWN;
        }
    }

    return token;
}

void tokenize(FILE *file, TokenArray *tokenArray) {
    Token token;
    tokenArray->size = 0;
    tokenArray->index = 0;

    while ((token = getNextToken(file)).type != TOKEN_EOF) {
        if (token.type != UNKNOWN) {
            if (tokenArray->size < MAX_TOKENS) {
                tokenArray->tokens[tokenArray->size++] = token;
            } else {
                fprintf(stderr, "ERROR: Too many tokens!\n");
                exit(1);
            }
        }
    }
}