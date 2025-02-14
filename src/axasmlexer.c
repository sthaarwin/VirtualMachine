#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "axasmlexer.h"

char *open_file(const char *filepath, int *length)
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

Token init_token(VM_Instructions type, char *text, int line, int charcter)
{
    Token token = {.type = type, .text = text, .line = line, .character = charcter};
    return token;
}

VM_Instructions check_builtin_keywords(char *name)
{
    printf("%s\n", name);
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
    return NOP;
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
    VM_Instructions type = check_builtin_keywords(keyword_name);
    token = init_token(type, keyword_name, line, character);
    return token;
}

int lexer()
{
    int length;
    const char *current = open_file("axasm/test.axasm", &length);
    int current_index = 0;

    int line = 0;
    int character = 0;

    while (current_index <= length)
    {
        if (isalpha(current[current_index]))
        {
            generate_keyword(current, &current_index, line, character);
        }
        else if (isdigit(current[current_index]))
        {
            printf("numeric ");
        }
        else if (current[current_index] == '\n')
        {
            line++;
        }
        current_index++;
    }
    printf("\n");
    return 0;
}