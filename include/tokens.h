#ifndef TOKENS_H
#define TOKENS_H

#define MAX_LEXEME_LENGTH 64
#define MAX_TOKENS 64

typedef enum {
    KEYWORD,
    IDENTIFIER,
    LPARENTHESIS,
    RPARENTHESIS,
    LBRACE,
    RBRACE,
    NUMBER_INT,
    SEMICOLON,
    TOKEN_EOF,
    UNKNOWN,
    NEGATION,
    BITWISE_COMPLEMENT,
    LOGICAL_NEGATION
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_LEXEME_LENGTH]; // actual characters of the token
} Token;

typedef struct{
    Token tokens[MAX_TOKENS];
    int size;
    int index; // holds index for token that will be read by next
} TokenArray;

#endif