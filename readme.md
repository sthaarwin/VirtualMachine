# Virtual Machine

This project implements a simple stack-based virtual machine in C. The virtual machine supports a variety of instructions for stack manipulation, arithmetic operations, comparisons, and control flow.

## Instructions

- `NOP`: No operation
- `PUSH x`: Push the operand `x` onto the stack
- `POP`: Pop the top value from the stack
- `ADD`: Pop the top two values, add them, and push the result
- `SUB`: Pop the top two values, subtract the top value from the second top value, and push the result
- `MUL`: Pop the top two values, multiply them, and push the result
- `DIV`: Pop the top two values, divide the second top value by the top value, and push the result
- `MOD`: Pop the top two values, compute the modulus, and push the result
- `PRINT`: Print the top value of the stack
- `DUP`: Duplicate the top value of the stack
- `SWAP`: Swap the top two values of the stack
- `CMPE`: Compare the top two values for equality and push the result (1 if equal, 0 otherwise)
- `CMPNE`: Compare the top two values for inequality and push the result (1 if not equal, 0 otherwise)
- `CMPG`: Compare if the second top value is greater than the top value and push the result
- `CMPL`: Compare if the second top value is less than the top value and push the result
- `CMPGE`: Compare if the second top value is greater than or equal to the top value and push the result
- `CMPLE`: Compare if the second top value is less than or equal to the top value and push the result
- `JMP x`: Jump to the instruction at index `x`
- `ZJMP x`: Pop the top value and jump to the instruction at index `x` if the value is zero
- `NZJMP x`: Pop the top value and jump to the instruction at index `x` if the value is not zero
- `HALT`: Halt the execution

## Running the Program

1. Compile the program:
    ```sh
    gcc -o bin/virtualMachine src/virtualMachine.c
    ```

2. Run the program:
    ```sh
    ./bin/virtualMachine
    ```

The program will execute the instructions defined in the `program` array and print the final state of the stack.

## Example

The provided example program performs a series of stack operations and arithmetic calculations. The final state of the stack will be printed after execution.
