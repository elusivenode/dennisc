
#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char peek(Lexer *lexer) { return *lexer->current; }

static char advance(Lexer *lexer) { return *lexer->current++; }

static int match(Lexer *lexer, char expected) {
  if (*lexer->current == expected) {
    lexer->current++;
    return 1;
  }
  return 0;
}

static void skip_whitespace(Lexer *lexer) {
  while (isspace(peek(lexer))) {
    advance(lexer);
  }
}

static int is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static int is_digit(char c) { return (c >= '0' && c <= '9'); }

static Token make_token(Lexer *lexer, TokenType type, const char *start) {
  Token token;
  token.type = type;
  token.start = start;
  token.length = (size_t)(lexer->current - start);
  return token;
}

static Token make_simple_token(Lexer *lexer, TokenType type) {
  return make_token(lexer, type, lexer->current - 1);
}

void lexer_init(Lexer *lexer, const char *source) {
  lexer->start = source;
  lexer->current = source;
}

static Token identifier(Lexer *lexer, const char *start) {
  while (is_alpha(peek(lexer)) || is_digit(peek(lexer))) {
    advance(lexer);
  }

  size_t length = lexer->current - start;
  if (length == 3 && strncmp(start, "int", 3) == 0) {
    return make_token(lexer, TOKEN_INT, start);
  }
  if (length == 6 && strncmp(start, "return", 6) == 0) {
    return make_token(lexer, TOKEN_RETURN, start);
  }

  return make_token(lexer, TOKEN_IDENTIFIER, start);
}

static Token number(Lexer *lexer, const char *start) {
  while (is_digit(peek(lexer))) {
    advance(lexer);
  }
  return make_token(lexer, TOKEN_NUMBER, start);
}

Token lexer_next_token(Lexer *lexer) {
  skip_whitespace(lexer);

  lexer->start = lexer->current;

  if (*lexer->current == '\0') {
    return make_token(lexer, TOKEN_EOF, lexer->current);
  }

  char c = advance(lexer);

  if (is_alpha(c)) {
    return identifier(lexer, lexer->start);
  }

  if (is_digit(c)) {
    return number(lexer, lexer->start);
  }

  switch (c) {
  case '(':
    return make_simple_token(lexer, TOKEN_LPAREN);
  case ')':
    return make_simple_token(lexer, TOKEN_RPAREN);
  case '{':
    return make_simple_token(lexer, TOKEN_LBRACE);
  case '}':
    return make_simple_token(lexer, TOKEN_RBRACE);
  case ';':
    return make_simple_token(lexer, TOKEN_SEMICOLON);
  case '=':
    return make_simple_token(lexer, TOKEN_ASSIGN);
  case '+':
    return make_simple_token(lexer, TOKEN_PLUS);
  default:
    return make_simple_token(lexer, TOKEN_UNKNOWN);
  }
}

void print_token(Token token) {
  printf("Token: ");
  switch (token.type) {
  case TOKEN_INT:
    printf("TOKEN_INT");
    break;
  case TOKEN_RETURN:
    printf("TOKEN_RETURN");
    break;
  case TOKEN_IDENTIFIER:
    printf("TOKEN_IDENTIFIER");
    break;
  case TOKEN_NUMBER:
    printf("TOKEN_NUMBER");
    break;
  case TOKEN_LPAREN:
    printf("TOKEN_LPAREN");
    break;
  case TOKEN_RPAREN:
    printf("TOKEN_RPAREN");
    break;
  case TOKEN_LBRACE:
    printf("TOKEN_LBRACE");
    break;
  case TOKEN_RBRACE:
    printf("TOKEN_RBRACE");
    break;
  case TOKEN_SEMICOLON:
    printf("TOKEN_SEMICOLON");
    break;
  case TOKEN_ASSIGN:
    printf("TOKEN_ASSIGN");
    break;
  case TOKEN_PLUS:
    printf("TOKEN_PLUS");
    break;
  case TOKEN_EOF:
    printf("TOKEN_EOF");
    break;
  case TOKEN_UNKNOWN:
    printf("TOKEN_UNKNOWN");
    break;
  }
  printf(" [length=%zu] '", token.length);
  for (size_t i = 0; i < token.length; i++) {
    putchar(token.start[i]);
  }
  printf("'\n");
}
