#include "Interpreter.h"
#include <string.h>
#include <stdio.h>

int divider(char *line, char **label, char **instruction, char **operands)
{
    char *rest;
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

    /*If the rest of the line is not null*/
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
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}
