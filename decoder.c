#include "decoder.h"

void decoder(char line[])
{

    int i;
    char *label, *cmd, *operands;
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
        cmds[i].func(operands);
    }
    else
    {
        printf("Command not found!\n");
    }
}


/*
int main()
{
    char line[] = "main: cmp  @r4   , @r2    ";
    printf("starting\n");
    decoder(line);

    return 0;
}
*/