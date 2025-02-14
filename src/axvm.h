#ifndef AXVM_H
#define AXVM_H

typedef enum
{
    NOP = 0,
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    DUP,
    INDUP,
    SWAP,
    INSWAP,
    CMPE,
    CMPNE,
    CMPG,
    CMPL,
    CMPGE,
    CMPLE,
    JMP,
    ZJMP,
    NZJMP,
    HALT
} VM_Instructions;

typedef struct
{
    VM_Instructions InstructionType;
    int operand;
} Instruction;

#define MAX_STACK_SIZE 1024

#define DEF_INST_NOP {.InstructionType = NOP}
#define DEF_INST_PUSH(x) {.InstructionType = PUSH, .operand = x}
#define DEF_INST_POP {.InstructionType = POP}
#define DEF_INST_ADD {.InstructionType = ADD}
#define DEF_INST_SUB {.InstructionType = SUB}
#define DEF_INST_MUL {.InstructionType = MUL}
#define DEF_INST_DIV {.InstructionType = DIV}
#define DEF_INST_PRINT {.InstructionType = PRINT}
#define DEF_INST_HALT {.InstructionType = HALT}
#define DEF_INST_DUP {.InstructionType = DUP}
#define DEF_INST_INDUP(x) {.InstructionType = INDUP, .operand = x}
#define DEF_INST_SWAP {.InstructionType = SWAP}
#define DEF_INST_INSWAP(x) {.InstructionType = INSWAP, .operand = x}
#define DEF_INST_CMPE {.InstructionType = CMPE}
#define DEF_INST_CMPNE {.InstructionType = CMPNE}
#define DEF_INST_CMPG {.InstructionType = CMPG}
#define DEF_INST_CMPL {.InstructionType = CMPL}
#define DEF_INST_CMPGE {.InstructionType = CMPGE}
#define DEF_INST_CMPLE {.InstructionType = CMPLE}
#define DEF_INST_JMP(x) {.InstructionType = JMP, .operand = x}
#define DEF_INST_ZJMP(x) {.InstructionType = ZJMP, .operand = x}
#define DEF_INST_NZJMP(x) {.InstructionType = NZJMP, .operand = x}

typedef struct
{
    int stack[MAX_STACK_SIZE];
    int stack_size;
    int program_size;
    Instruction *instructions;
} Machine;

void push(Machine *machine, int value);
int pop(Machine *machine);
int peek(Machine *machine);
void index_dup(Machine *machine, int index);
void index_swap(Machine *machine, int index);
void print_stack(Machine *machine);
void write_program_to_file(const char *file_path);
Machine *read_program_from_file(const char *file_path, int *program_size);
void run_instructions(Machine *machine);

#include "axasmlexer.h"

#endif // AXVM_H