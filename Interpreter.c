/*interpreter.c
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: define functions related to parsing and manipulating lines of code in an assembly language interpreter program. The functions are responsible for dividing a line into its constituent parts (label, instruction, and operands), as well as removing spaces, tabs, and newlines from strings. This code assists in the initial processing of input lines to extract relevant information and clean up any unnecessary characters. */

#include "Interpreter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Function to divide a line into label, instruction, and operands */
int divider(char *line, char **label, char **instruction, char **operands)
{
    char *rest;
    int j, empty;
    char *line_cpy;
    line_cpy = (char *)malloc(strlen(line) * sizeof(char));
    strcpy(line_cpy, line);

    /* Check if this is a comment line */
    if (!strncmp(line_cpy, ";", 1))
    {
        *label = NULL;
        *instruction = NULL;
        *operands = NULL;
        return IS_COMMENT_EMPTY;
    }

    /* Discard comment in line */
    strtok(line_cpy, ";");

    /* Get the label */
    *label = strtok(line_cpy, ":");
    rest = strtok(NULL, "");

    /* If there is no label */
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

    /* If the rest of the line is not null */
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

/* Function to remove spaces, tabs, and newlines from a string */
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
