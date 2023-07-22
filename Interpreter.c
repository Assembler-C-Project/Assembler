#include "Interpreter.h"
#include <string.h>
#include <stdio.h>

void divider(char *line, char **label, char **instruction, char **operands)
{
    char *rest;
    *label = strtok(line, ":");
    rest = strtok(NULL, "");
    
    if (rest == NULL || strlen(rest) == 0)
    {
        if (*label != NULL)
            rest = *label;
        else
            rest = "";
        *label = NULL;
    }

    if (strlen(rest) > 0)
    {
        *instruction = strtok(rest, " ");
        *operands = strtok(NULL, "");
        if (*operands != NULL)
        {
            remove_spaces(*operands);
        }
        if (*instruction != NULL)
        {
            remove_spaces(*instruction);
        }
    }
    else
    {
        *instruction = NULL;
        *operands = NULL;
    }
}
void remove_spaces(char *str)
{

    int i;
    int count;
    count = 0;
    for (i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}
