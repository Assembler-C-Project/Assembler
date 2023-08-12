#include "decoder.h"

cmd cmds[] =
    {{"mov", MOV}, {"cmp", CMP}, {"add", ADD}, {"sub", SUB}, {"not", NOT}, {"clr", CLR}, {"lea", LEA}, {"inc", INC}, {"dec", DEC}, {"jmp", JMP}, {"bne", BNE}, {"red", RED}, {"prn", PRN}, {"jsr", JSR}, {"rts", RTS}, {"stop", STOP}};
inst insts[] = {
    {".data", IS_DATA}, {".string", IS_STRING}, {".entry", IS_ENTRY}, {".extern", IS_EXTERN}};
int decoder(char *line, int line_num, int *IC, int *DC, char ***base64Chars)
{

    int i;
    char *label, *comd, *operands;
    int err_msg;
    int line_type;
    err_msg = -1;
    line_type = divider(line, &label, &comd, &operands);
    if (label != NULL && !is_valid_label(label))
    {
        err_msg = ERR_INV_LABEL;
    }

    printf("%s: %s %s\n", label, comd, operands);
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
            err_msg = functions(cmds[i].value, operands, IC, DC, base64Chars);
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
            err_msg = functions(insts[i].value, operands, IC, DC, base64Chars);
        }
        else
        {
            printf("ERR: Wrong instruction found!\n");
        }
        break;
    case IS_COMMENT_EMPTY:
        break;
    }
    return err_msg;
}

void RunDecoder(FILE *SourceFile, char *fileName)
{
    LabelNode *lables = NULL;
    FILE *objectFile;
    char line[MAX_LINE_LENGTH];
    int i;
    char **base64Chars;
    int err_msg;
    int IC, DC;
    char IC_DC[30];
    base64Chars = (char **)malloc(3 * sizeof(char *));
    i = 0;
    IC = 0;
    DC = 0;
    strtok(fileName, ".");

    fileName = strcat(fileName, ".ob");
    if ((objectFile = fopen(fileName, "w")) == NULL)
    {
        printf("Cannot open file %s\n", fileName);
        return;
    }

    printf("starting\n");
    runFirstPass(SourceFile, lables);
    rewind(SourceFile);
    while (fgets(line, MAX_LINE_LENGTH, SourceFile) != NULL)
    {
        err_msg = decoder(line, i, &IC, &DC, &base64Chars);
        if (err_msg != -1)
        {
            printf("Error in line %d: %s\n", i + 1, error[err_msg].message);
        }
        i++;
    }
    i = 0;
    sprintf(IC_DC, "%d %d\n", IC, DC);
    fputs(IC_DC, objectFile);

    while (base64Chars[i] != '\0')
    {
        fputs(base64Chars[i], objectFile);
        fputs("\n", objectFile);
        i++;
    }
}
