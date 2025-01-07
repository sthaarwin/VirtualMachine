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

typedef struct{
    VM_Instructions InstructionType;
    int operand; 
}Instruction;

Instruction program[] = {
   {.InstructionType = PUSH, .operand = 10}, 
   {.InstructionType = PRINT},
   {.InstructionType = POP},
};

#define PROGRAM_SIZE (sizeof(program)/sizeof(program[0]))
#define MAX_STACK_SIZE 1024

int stack[MAX_STACK_SIZE];
int stack_size = 0;

void push(int value){
    stack[stack_size++] = value;
}

int pop(){
    return stack[--stack_size];
}


int main(){
    size_t ip = 0;
    for(ip = 0; ip < PROGRAM_SIZE; ip++){
        switch(program[ip].InstructionType){
            case PUSH:
                push(program[ip].operand); 
                break;

            case POP:
                printf("POP %d\n", pop());
                break;

            case PRINT:
                printf("PRINT\n");
                break;
            
            default:
                assert(0 && "Unknown Instruction");
        }
    }
    return 0;
}