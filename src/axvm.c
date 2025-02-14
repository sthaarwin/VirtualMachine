#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "axvm.h"

Instruction program[] = {
    DEF_INST_PUSH(10),
    DEF_INST_PUSH(20),
    DEF_INST_PUSH(30),
    DEF_INST_PUSH(40),
    DEF_INST_INDUP(1),
    DEF_INST_INSWAP(1),
    DEF_INST_HALT,
};

void push(Machine *machine, int value)
{
    if (machine->stack_size >= MAX_STACK_SIZE)
    {
        fprintf(stderr, "Stack Overflow\n");
        exit(1);
    }
    machine->stack[machine->stack_size++] = value;
}

int pop(Machine *machine)
{
    if (machine->stack_size == 0)
    {
        fprintf(stderr, "Stack Underflow\n");
        exit(1);
    }
    return machine->stack[--machine->stack_size];
}

int peek(Machine *machine)
{
    if (machine->stack_size == 0)
    {
        fprintf(stderr, "Stack Underflow\n");
        exit(1);
    }
    return machine->stack[machine->stack_size - 1];
}

void index_dup(Machine *machine, int index)
{
    if (index >= machine->stack_size || index < 0)
    {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    push(machine, machine->stack[index]);
}

void index_swap(Machine *machine, int index)
{
    if (index >= machine->stack_size || index < 0)
    {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    int temp = machine->stack[index];
    machine->stack[index] = pop(machine);
    push(machine, temp);
}

void print_stack(Machine *machine)
{
    printf("----------Start of Stack---------------\n");
    for (int i = machine->stack_size - 1; i >= 0; i--)
    {
        printf("%d\n", machine->stack[i]);
    }
    printf("----------End of Stack---------------\n");
}

void write_program_to_file(const char *file_path)
{
    FILE *file = fopen(file_path, "wb");
    if (file == NULL)
    {
        fprintf(stderr, "ERROR : could not write to file %s\n", file_path);
        exit(1);
    }

    fwrite(program, sizeof(program[0]), sizeof(program) / sizeof(program[0]), file);

    fclose(file);
}

Machine *read_program_from_file(const char *file_path, int *program_size)
{
    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "ERROR : could not read from file %s\n", file_path);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *program_size = length / sizeof(Instruction);
    Instruction *instructions = (Instruction *)malloc(length);
    Machine *machine = (Machine *)malloc(sizeof(Machine));

    fread(instructions, sizeof(Instruction), *program_size, file);
    machine->program_size = *program_size;
    machine->instructions = instructions;

    fclose(file);
    return machine;
}

void run_instructions(Machine *machine)
{
    int a, b;
    size_t ip = 0;
    for (ip = 0; ip < machine->program_size; ip++)
    {
        switch (machine->instructions[ip].InstructionType)
        {
        case NOP:
            continue;
            break;

        case PUSH:
            push(machine, machine->instructions[ip].operand);
            break;

        case POP:
            pop(machine);
            break;

        case PRINT:
            printf("PEEK %d\n", peek(machine));
            break;

        case ADD:
            a = pop(machine);
            b = pop(machine);
            push(machine, a + b);
            break;

        case SUB:
            a = pop(machine);
            b = pop(machine);
            push(machine, b - a);
            break;

        case MUL:
            a = pop(machine);
            b = pop(machine);
            push(machine, a * b);
            break;

        case DIV:
            a = pop(machine);
            b = pop(machine);
            if (a == 0)
            {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            push(machine, b / a);
            break;

        case MOD:
            a = pop(machine);
            b = pop(machine);
            if (a == 0)
            {
                fprintf(stderr, "Division by zero\n");
                exit(1);
            }
            push(machine, b % a);
            break;

        case DUP:
            push(machine, peek(machine));
            break;

        case INDUP:
            index_dup(machine, machine->instructions[ip].operand);
            break;

        case SWAP:
            a = pop(machine);
            b = pop(machine);
            push(machine, a);
            push(machine, b);
            break;

        case INSWAP:
            index_swap(machine, machine->instructions[ip].operand);
            break;

        case CMPE:
            a = pop(machine);
            b = pop(machine);
            push(machine, b);
            push(machine, a);
            push(machine, a == b);
            break;

        case CMPNE:
            a = pop(machine);
            b = pop(machine);
            push(machine, b);
            push(machine, a);
            push(machine, a != b);
            break;

        case CMPG:
            a = pop(machine);
            b = pop(machine);
            push(machine, b);
            push(machine, a);
            push(machine, a > b);
            break;

        case CMPL:
            a = pop(machine);
            b = pop(machine);
            push(machine, b);
            push(machine, a);
            push(machine, a < b);
            break;

        case CMPGE:
            a = pop(machine);
            b = pop(machine);
            push(machine, b);
            push(machine, a);
            push(machine, a >= b);
            break;

        case CMPLE:
            a = pop(machine);
            b = pop(machine);
            push(machine, b);
            push(machine, a);
            push(machine, a <= b);
            break;

        case ZJMP:
            a = pop(machine);
            if (a == 0)
            {
                ip = machine->instructions[ip].operand - 1;
                if (ip + 1 >= machine->program_size)
                {
                    fprintf(stderr, "ERROR : cannot jump out of bounds\n");
                    exit(1);
                }
            }
            else
                continue;
            break;

        case NZJMP:
            a = pop(machine);
            if (a != 0)
            {
                ip = machine->instructions[ip].operand - 1;
                if (ip + 1 >= machine->program_size)
                {
                    fprintf(stderr, "ERROR : cannot jump out of bounds\n");
                    exit(1);
                }
            }
            else
                continue;
            break;

        case JMP:
            ip = machine->instructions[ip].operand - 1;
            if (ip + 1 >= machine->program_size)
            {
                fprintf(stderr, "ERROR : cannot jump out of bounds\n");
                exit(1);
            }
            break;

        case HALT:
            ip = machine->program_size;
            break;

        default:
            assert(0 && "Unknown Instruction");
        }
    }
}

int main()
{
    lexer();
    int a, b;
    write_program_to_file("bin/axzyte.axbin");
    int program_size;
    Machine *LoadedMachine = read_program_from_file("bin/axzyte.axbin", &program_size);
    run_instructions(LoadedMachine);
    print_stack(LoadedMachine);
    free(LoadedMachine->instructions);
    free(LoadedMachine);
    return 0;
}