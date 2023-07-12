#include "Interpreter.h"

void divider(char *line, char **label, char **instruction, char **operands)
{
    char *rest;
    *label = strtok(line, ":");
    rest = strtok(NULL, "");
    if (rest == NULL)
    {
        rest = *label;
        *label = NULL;
    }
    *instruction = strtok(rest, " ");
    *operands = strtok(NULL, "");
    remove_spaces( *operands);
    remove_spaces(*instruction);

}
void remove_spaces(char *str){

  
    int i;
    int count;
    count = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] != ' ') {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}
