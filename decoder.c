#include "decoder.h"

void decoder(char *line, int line_num)
{
    int i;
    char *label, *cmd, *operands;
    int err_msg;
    divider(line, &label, &cmd, &operands);
    i = 0;
    while (i < 16)
    {
        if (!strcmp(cmd, cmds[i].name))
        {
            break;
        }
        i++;
    }
    if (i != 16)
    {
        err_msg = functions(cmds[i].value, operands);
        if (err_msg != -1)
        {
            printf("Error in line %d: %s\n", line_num, error[err_msg].message);
        }
    }
    else
    {
        printf("ERR: Wrong command found!\n");
    }
}

int main()
{
    FILE* sourceFile = fopen("output_file.txt", "r");
    char line[MAX_LINE_LENGTH];
    int i = 0;

    /* Check if the source file opened successfully */
    if (sourceFile == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    printf("starting\n");

    while(fgets(line, MAX_LINE_LENGTH, sourceFile) != NULL)
    {
        decoder(line, i);
        i++;
    }

    return 0;
}
