#include "decoder.h"

cmd cmds[] =
    {{"mov", MOV}, {"cmp", CMP}, {"add", ADD}, 
    {"sub", SUB}, {"not", NOT}, {"clr", CLR}, 
    {"lea", LEA}, {"inc", INC}, {"dec", DEC}, 
    {"jmp", JMP}, {"bne", BNE}, {"red", RED}, 
    {"prn", PRN}, {"jsr", JSR}, {"rts", RTS}, 
    {"stop", STOP}};


void decoder(char *line, int line_num)
{
    int i;
    char *label, *comd, *operands;
    int err_msg;
    divider(line, &label, &comd, &operands);
    i = 0;
    while (i < 16)
    {
        if (!strcmp(comd, cmds[i].name))
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

void RunDecoder(FILE *SourceFile)
{
    char line[MAX_LINE_LENGTH];
    int i = 0;
    printf("starting\n");
    while(fgets(line, MAX_LINE_LENGTH, SourceFile) != NULL)
    {
        decoder(line, i);
        i++;
    }
}
