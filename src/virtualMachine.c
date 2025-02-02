#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum
{
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    PRINT,
    HALT
} VM_Instructions;

typedef struct
{
    VM_Instructions InstructionType;
    int operand;
} Instruction;

#define DEF_INST_PUSH(x) {.InstructionType = PUSH, .operand = x}
#define DEF_INST_POP {.InstructionType = POP}
#define DEF_INST_ADD {.InstructionType = ADD}
#define DEF_INST_SUB {.InstructionType = SUB}
#define DEF_INST_MUL {.InstructionType = MUL}
#define DEF_INST_DIV {.InstructionType = DIV}
#define DEF_INST_PRINT {.InstructionType = PRINT}
#define DEF_INST_HALT {.InstructionType = HALT}

Instruction program[] = {
    DEF_INST_PUSH(20),
    DEF_INST_PUSH(10),
    DEF_INST_SUB,
};

#define PROGRAM_SIZE (sizeof(program) / sizeof(program[0]))
#define MAX_STACK_SIZE 1024

int stack[MAX_STACK_SIZE];
int stack_size = 0;

void push(int value)
{
    if (stack_size >= MAX_STACK_SIZE)
    {
        fprintf(stderr, "Stack Overflow\n");
        exit(1);
    }
    stack[stack_size++] = value;
}

int pop()
{
    if (stack_size == 0)
    {
        fprintf(stderr, "Stack Underflow\n");
        exit(1);
    }
    return stack[--stack_size];
}

int peek()
{
    if (stack_size == 0)
    {
        fprintf(stderr, "Stack Underflow\n");
        exit(1);
    }
    return stack[stack_size - 1];
}

void print_stack()
{
    printf("Stack: ");
    for (int i = stack_size - 1; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main()
{
    int a, b;
    size_t ip = 0;
    for (ip = 0; ip < PROGRAM_SIZE; ip++)
    {
        switch (program[ip].InstructionType)
        {
        case PUSH:
            push(program[ip].operand);
            break;

        case POP:
            pop();
            break;

        case PRINT:
            printf("PEEK %d\n", peek());
            break;

        case ADD:
            a = pop();
            b = pop();
            push(a + b);
            break;

        case SUB:
            a = pop();
            b = pop();
            push(b - a);
            break;

        case MUL:
            a = pop();
            b = pop();
            push(a * b);
            break;

        case DIV:
            a = pop();
            b = pop();
            push(b / a);
            break;

        case HALT:
            printf("HALT\n");
            break;

        default:
            assert(0 && "Unknown Instruction");
        }
    }
    print_stack();
    return 0;
}