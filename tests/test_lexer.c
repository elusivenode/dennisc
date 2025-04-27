#include "unity.h"
#include "../lexer.h"
#include <string.h>

void setUp(void) {
    // This function is called before each test
}

void tearDown(void) {
    // This function is called after each test
}

void test_lexer_initialization(void) {
    Lexer lexer;
    const char* source = "int x = 42;";
    lexer_init(&lexer, source);
    
    TEST_ASSERT_EQUAL_PTR(source, lexer.start);
    TEST_ASSERT_EQUAL_PTR(source, lexer.current);
}

void test_token_creation(void) {
    Lexer lexer;
    const char* source = "int x = 42;";
    lexer_init(&lexer, source);
    
    // Test first token (should be TOKEN_INT)
    Token token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_INT, token.type);
    TEST_ASSERT_EQUAL(3, token.length); // "int" is 3 characters
    
    // Test second token (should be TOKEN_IDENTIFIER)
    token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, token.type);
    TEST_ASSERT_EQUAL(1, token.length); // "x" is 1 character
    
    // Test third token (should be TOKEN_ASSIGN)
    token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_ASSIGN, token.type);
    TEST_ASSERT_EQUAL(1, token.length); // "=" is 1 character
    
    // Test fourth token (should be TOKEN_NUMBER)
    token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_NUMBER, token.type);
    TEST_ASSERT_EQUAL(2, token.length); // "42" is 2 characters
    
    // Test fifth token (should be TOKEN_SEMICOLON)
    token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_SEMICOLON, token.type);
    TEST_ASSERT_EQUAL(1, token.length); // ";" is 1 character
}

void test_whitespace_handling(void) {
    Lexer lexer;
    const char* source = "  int   x   =   42  ;  ";
    lexer_init(&lexer, source);
    
    // Test that whitespace is properly skipped
    Token token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_INT, token.type);
    TEST_ASSERT_EQUAL(3, token.length);
    
    token = lexer_next_token(&lexer);
    TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER, token.type);
    TEST_ASSERT_EQUAL(1, token.length);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_lexer_initialization);
    RUN_TEST(test_token_creation);
    RUN_TEST(test_whitespace_handling);
    
    return UNITY_END();
} 