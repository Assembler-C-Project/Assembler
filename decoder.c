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
        functions(cmds[i].value, operands);
    }
    else
    {
        printf("ERR: Wrong command found!\n");
    }
}

int main()
{
    char line[2][30];

    strcpy((line[0]), "inc K");
    strcpy((line[1]), "sub @r1, @r4");
    printf("starting\n");

    decoder(line[0]);
    decoder(line[1]);

    return 0;
}
