#ifndef LEXER_H
#define LEXER_H

#include <stddef.h> // for size_t

typedef enum {
    TOKEN_INT,
    TOKEN_RETURN,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_LPAREN,    // (
    TOKEN_RPAREN,    // )
    TOKEN_LBRACE,    // {
    TOKEN_RBRACE,    // }
    TOKEN_SEMICOLON, // ;
    TOKEN_ASSIGN,    // =
    TOKEN_PLUS,      // +
    TOKEN_EOF,
    TOKEN_UNKNOWN,
} TokenType;

typedef struct {
    TokenType type;
    const char *start;  // Pointer into original source
    size_t length;      // Length of the token
} Token;

typedef struct {
    const char *start;   // Start of current token
    const char *current; // Current character
} Lexer;

// Initialize a lexer from a source string
void lexer_init(Lexer *lexer, const char *source);

// Get the next token
Token lexer_next_token(Lexer *lexer);

// Helper to print a token (for debugging)
void print_token(Token token);

#endif // LEXER_H

