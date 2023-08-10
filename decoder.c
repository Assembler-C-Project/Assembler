#include "decoder.h"

cmd cmds[] =
    {{"mov", MOV}, {"cmp", CMP}, {"add", ADD}, {"sub", SUB}, {"not", NOT}, {"clr", CLR}, {"lea", LEA}, {"inc", INC}, {"dec", DEC}, {"jmp", JMP}, {"bne", BNE}, {"red", RED}, {"prn", PRN}, {"jsr", JSR}, {"rts", RTS}, {"stop", STOP}};
inst insts[] = {
    {".data", IS_DATA}, {".string", IS_STRING}, {".entry", IS_ENTRY}, {".extern", IS_EXTERN}};
void decoder(char *line, int line_num, FILE *objectFile)
{
    int i;
    char *label, *comd, *operands;
    int err_msg;
    int line_type;
    err_msg = -1;
    line_type = divider(line, &label, &comd, &operands);
    if (!is_valid_label(label))
    {
        err_msg = ERR_INV_LABEL;
    }
    if (err_msg != -1)
    {
        printf("Error in line %d: %s\n", line_num, error[err_msg].message);
    }
    printf("%s: %s %s", label, comd, operands);
    switch (line_type)
    {
    case IS_COMMAND:
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
            err_msg = functions(cmds[i].value, operands, objectFile);
            if (err_msg != -1)
            {
                printf("Error in line %d: %s\n", line_num, error[err_msg].message);
            }
        }
        else
        {
            printf("ERR: Wrong command found!\n");
        }
        break;
    case IS_INSTRUCTION:
        i = 0;
        while (i < 4)
        {
            if (!strcmp(comd, insts[i].name))
            {
                break;
            }
            i++;
        }
        if (i != 4)
        {
            err_msg = functions(insts[i].value, operands, objectFile);
            if (err_msg != -1)
            {
                printf("Error in line %d: %s\n", line_num, error[err_msg].message);
            }
        }
        else
        {
            printf("ERR: Wrong instruction found!\n");
        }

        break;
    }
}

void RunDecoder(FILE *SourceFile, char *fileName)
{
    FILE *objectFile;
    char line[MAX_LINE_LENGTH];
    int i = 0;

    strtok(fileName, ".");

    fileName = strcat(fileName, ".ob");
    if ((objectFile = fopen(fileName, "w")) == NULL)
    {
        printf("Cannot open file %s\n", fileName);
        return;
    }

    printf("starting\n");
    while (fgets(line, MAX_LINE_LENGTH, SourceFile) != NULL)
    {
        decoder(line, i, objectFile);
        i++;
    }
}
