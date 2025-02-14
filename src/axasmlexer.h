#ifndef AXASMLEXER_H
#define AXASMLEXER_H

#include "axvm.h"

typedef struct{
    VM_Instructions type;
    char *text;
    int line;
    int character;
}Token;

char *open_file(char *filepath, int *length);
int lexer();
#endif // AXASMLEXER_H