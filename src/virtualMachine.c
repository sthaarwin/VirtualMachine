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


#define MAX_STACK_SIZE 1024


#define DEF_INST_PUSH(x) {.InstructionType = PUSH, .operand = x}
#define DEF_INST_POP {.InstructionType = POP}
#define DEF_INST_ADD {.InstructionType = ADD}
#define DEF_INST_SUB {.InstructionType = SUB}
#define DEF_INST_MUL {.InstructionType = MUL}
#define DEF_INST_DIV {.InstructionType = DIV}
#define DEF_INST_PRINT {.InstructionType = PRINT}
#define DEF_INST_HALT {.InstructionType = HALT}


typedef struct
{
   int stack[MAX_STACK_SIZE];
   int stack_size;
   int program_size;
   Instruction *instructions;
} Machine;



Instruction program[] = {
    DEF_INST_PUSH(20),
    DEF_INST_PUSH(10),
    DEF_INST_PUSH(5),
    DEF_INST_PUSH(2),
    DEF_INST_ADD,
};


void push(int value, Machine* machine)
{
    if (machine->stack_size >= MAX_STACK_SIZE)
    {
        fprintf(stderr, "Stack Overflow\n");
        exit(1);
    }
    machine->stack[machine->stack_size++] = value;
}

int pop(Machine* machine)
{
    if (machine->stack_size == 0)
    {
        fprintf(stderr, "Stack Underflow\n");
        exit(1);
    }
    return machine->stack[--machine->stack_size];
}

int peek(Machine* machine)
{
    if (machine->stack_size == 0)
    {
        fprintf(stderr, "Stack Underflow\n");
        exit(1);
    }
    return machine->stack[machine->stack_size - 1];
}

void print_stack(Machine *machine)
{
    printf("Stack: ");
    for (int i = machine->stack_size - 1; i >= 0; i--)
    {
        printf("%d ", machine->stack[i]);
    }
    printf("\n");
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
    Instruction *instructions = (Instruction*)malloc(length);
    Machine *machine = (Machine*)malloc(sizeof(Machine));

    fread(instructions, sizeof(Instruction), *program_size, file);
    machine->program_size = *program_size;
    machine->instructions = instructions;

    fclose(file);
    return machine;
}

int main()
{
    int a, b;
    write_program_to_file("output/axzyte.axbin");
    int program_size;
    Machine *machine = read_program_from_file("output/axzyte.axbin", &program_size);
    size_t ip = 0;
    for (ip = 0; ip < program_size; ip++)
    {
        switch (machine->instructions[ip].InstructionType)
        {
        case PUSH:
            push(machine->instructions[ip].operand, machine);
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
            push(a + b, machine);
            break;

        case SUB:
            a = pop(machine);
            b = pop(machine);
            push(b - a, machine);
            break;

        case MUL:
            a = pop(machine);
            b = pop(machine);
            push(a * b, machine);
            break;

        case DIV:
            a = pop(machine);
            b = pop(machine);
            push(b / a, machine);
            break;

        case HALT:
            printf("HALT\n");
            break;

        default:
            assert(0 && "Unknown Instruction");
        }
    }
    print_stack(machine);
    free(machine->instructions);
    free(machine);
    return 0;
}