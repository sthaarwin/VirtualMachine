#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef enum{
    PUSH,
    POP,
    ADD, 
    SUB,
    MUL,
    DIV,
    PRINT,
    HALT
}VM_Instructions;

int main(){
    printf("Hello World");
    return 0;
}