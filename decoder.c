#include "decoder.h"

void decoder(char **lines, int line_num)
{
    char line[30];
    int i;
    char *label, *cmd, *operands;
    int err_msg;
    strcpy(line, lines[line_num]);
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
/*
int main()
{
    char *lines[2] = {"inc 5,s", "stop "};

    printf("starting\n");

    decoder(lines, 0);
    decoder(lines, 1);

    return 0;
}
*/