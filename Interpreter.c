#include "Interpreter.h"
#include <string.h>
#include <stdio.h>

int divider(char *line, char **label, char **instruction, char **operands)
{
    char *rest;
    int j, empty;
    /*Check if this is a comment line*/
    if (!strncmp(line, ";", 1))
    {

        label = NULL;
        instruction = NULL;
        operands = NULL;
        return IS_COMMENT_EMPTY;
    }
    /*Discard comment in line*/
    strtok(line, ";");

    /*Get the label*/
    *label = strtok(line, ":");
    rest = strtok(NULL, "");
    /*If there is no label*/
    if (rest == NULL || strlen(rest) == 0)
    {
        if (*label != NULL)
            rest = *label;
        else
            rest = "";
        *label = NULL;
    }
    empty = 1;
    j = 0;
    /*If the rest of the line is not null*/

    while (empty == 1 && j < strlen(rest))
    {
        if (rest[j] != '\n' && rest[j] != '\t' && rest[j] != '\0' && rest[j] != ' ')
        {
            empty = 0;
        }
        j++;
    }

    if (strlen(rest) > 0 && !empty)
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
            if (!strncmp(*instruction, ".", 1))
            {
                return IS_INSTRUCTION;
            }
            return IS_COMMAND;
        }
    }
    else
    {
        *instruction = NULL;
        *operands = NULL;
    }
    return IS_COMMENT_EMPTY;
}

void remove_spaces(char *str)
{

    int i;
    int count;
    count = 0;
    for (i = 0; str[i]; i++)
    {
        if (str[i] != ' ' && str[i] != '\0' && str[i] != '\n' && str[i] != '\t')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}
