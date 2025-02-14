#ifndef AXASMLEXER_H
#define AXASMLEXER_H

#include "axvm.h"

#define MAX_TOKEN_STACK_SIZE 1024
typedef struct{
    VM_Instructions type;
    char *text;
    int line;
    int character;
}Token;

typedef struct{
    Token token_stack[MAX_TOKEN_STACK_SIZE];
    char *file_name;
    int stack_size;
}Lexer;

char *open_file( char *filepath, int *length);
int lexer();
#endif // AXASMLEXER_H