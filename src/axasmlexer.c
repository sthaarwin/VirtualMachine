#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "axasmlexer.h"

char *open_file(char *filepath, int *length)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        fprintf(stderr, "ERROR : cound not open file %s\n", filepath);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *current = (char *)malloc(sizeof(char) * *length);
    fread(current, 1, *length, file);

    if (!current)
    {
        fprintf(stderr, "ERROR : could not read the file %s\n", filepath);
        exit(1);
    }

    fclose(file);
    return current;
}

void push_token(Lexer *lexer, Token value){
    if(lexer->stack_size >= MAX_TOKEN_STACK_SIZE){
        fprintf(stderr, "ERROR : stack overflow\n");
        exit(1);
    }
    lexer->token_stack[lexer->stack_size] = value;
    lexer->stack_size++;
}

Token pop_token(Lexer *lexer){
    if(lexer->stack_size <= 0){
        fprintf(stderr, "ERROR : stack underflow\n");
        exit(1);
    }
    lexer->stack_size--;
    return lexer->token_stack[lexer->stack_size];
}

void print_token(Token token)
{
    printf("text : %s line : %d character : %d\n", token.text, token.line, token.character);
}

Token init_token(VM_Instructions type, char *text, int line, int charcter)
{
    Token token = {.type = type, .text = text, .line = line, .character = charcter};
    return token;
}

VM_Instructions check_builtin_keywords(char *name)
{
    if (strcmp(name, "nop") == 0)
    {
        return NOP;
    }

    else if (strcmp(name, "push") == 0)
    {
        return PUSH;
    }

    else if (strcmp(name, "pop") == 0)
    {
        return POP;
    }

    else if (strcmp(name, "add") == 0)
    {
        return ADD;
    }

    else if (strcmp(name, "sub") == 0)
    {
        return SUB;
    }

    else if (strcmp(name, "mul") == 0)
    {
        return MUL;
    }

    else if (strcmp(name, "div") == 0)
    {
        return DIV;
    }

    else if(strcmp(name, "mod") == 0)
    {
        return MOD;
    }

    else if (strcmp(name, "print") == 0)
    {
        return PRINT;
    }

    else if (strcmp(name, "halt") == 0)
    {
        return HALT;
    }

    else if (strcmp(name, "dup") == 0)
    {
        return DUP;
    }

    else if (strcmp(name, "indup") == 0)
    {
        return INDUP;
    }

    else if (strcmp(name, "swap") == 0)
    {
        return SWAP;
    }

    else if (strcmp(name, "inswap") == 0)
    {
        return INSWAP;
    }

    else if (strcmp(name, "cmpe") == 0)
    {
        return CMPE;
    } 

    else if (strcmp(name, "cmpne") == 0)
    {
        return CMPNE;
    }

    else if (strcmp(name, "cmpg") == 0)
    {
        return CMPG;
    }

    else if (strcmp(name, "cmpl") == 0)
    {
        return CMPL;
    }

    else if (strcmp(name, "cmpge") == 0)
    {
        return CMPGE;
    }

    else if (strcmp(name, "cmple") == 0)
    {
        return CMPLE;
    }

    else if (strcmp(name, "jmp") == 0)
    {
        return JMP;
    }

    else if (strcmp(name, "zjmp") == 0)
    {
        return ZJMP;
    }

    else if (strcmp(name, "nzjmp") == 0)
    {
        return NZJMP;
    }

    else if (strcmp(name, "halt") == 0)
    {
        return HALT;
    }

    else
    {
        printf("ERROR : unknown keyword %s\n", name);
        return NONE;
    }
}

Token generate_keyword(const char *current, int *current_index, int line, int character)
{
    Token token;

    char keyword_name[256];
    int keyword_length = 0;

    while (isalpha(current[*current_index]))
    {
        keyword_name[keyword_length] = current[*current_index];
        (*current_index)++;
        keyword_length++;
    }
    keyword_name[keyword_length] = '\0';

    token.text = (char *)malloc((keyword_length + 1) * sizeof(char));
    strcpy(token.text, keyword_name);

    VM_Instructions type = check_builtin_keywords(keyword_name);
    assert(type != NONE && "ERROR : unknown keyword");
    token = init_token(type, token.text, line, character);
    return token;
}

Token generate_int(const char *current, int *current_index, int line, int character)
{
    Token token;
    char keyword_name[16];
    int keyword_length = 0;

    while (isdigit(current[*current_index]))
    {
        keyword_name[keyword_length] = current[*current_index];
        (*current_index)++;
        keyword_length++;
    }
    keyword_name[keyword_length] = '\0';

    token.text = (char *)malloc((keyword_length + 1) * sizeof(char));
    strcpy(token.text, keyword_name);

    VM_Instructions type = INT;
    token = init_token(type, token.text, line, character);
    return token;
}

int lexer()
{
    Lexer lexer = {.file_name = "axasm/test.axasm", .stack_size = 0};
    int length;
    const char *current = open_file("axasm/test.axasm", &length);
    int current_index = 0;

    int line = 1;
    int character = 1;

    while (current_index < length)
    {
        if (isalpha(current[current_index]))
        {
            Token token = generate_keyword(current, &current_index, line, character);
            push_token(&lexer, token);
            current_index--;
            // print_token(token);
        }
        else if (isdigit(current[current_index]))
        {
            Token token = generate_int(current, &current_index, line, character);
            push_token(&lexer, token); 
            current_index--;
            // print_token(token);
        }
        else if (current[current_index] == '\n')
        {
            line++;
            character = 0;
        }
        else if(current[current_index] == ' '){
            character--;
        }
        current_index++;
        character++;
    }
    printf("\n");

    for (int i = 0; i < lexer.stack_size; i++)
    {
        print_token(lexer.token_stack[i]);
    }
    return 0;
}