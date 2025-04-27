cmake_minimum_required(VERSION 3.10)
project(dennisc C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add Unity as a subdirectory
add_subdirectory(vendor/unity)

# Main library
add_library(dennisc
    lexer.c
)

# Include directories
target_include_directories(dennisc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Tests
add_executable(test_lexer
    tests/test_lexer.c
)

# Link tests with our library and Unity
target_link_libraries(test_lexer
    dennisc
    unity
)

# Include directories for tests
target_include_directories(test_lexer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${UNITY_INCLUDE_DIRS}
)

# Enable testing
enable_testing()
add_test(NAME test_lexer COMMAND test_lexer) 