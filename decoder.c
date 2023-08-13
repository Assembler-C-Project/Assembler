#include "decoder.h"

cmd cmds[] =
    {{"mov", MOV}, {"cmp", CMP}, {"add", ADD}, {"sub", SUB}, {"not", NOT}, {"clr", CLR}, {"lea", LEA}, {"inc", INC}, {"dec", DEC}, {"jmp", JMP}, {"bne", BNE}, {"red", RED}, {"prn", PRN}, {"jsr", JSR}, {"rts", RTS}, {"stop", STOP}};
inst insts[] = {
    {".data", IS_DATA}, {".string", IS_STRING}, {".entry", IS_ENTRY}, {".extern", IS_EXTERN}};
int decoder(char *line, int line_num, int *IC, int *DC, char ***base64Chars, mem_word **label_lst, char *filename)
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
            err_msg = functions(cmds[i].value, operands, IC, DC, base64Chars, *label_lst, filename);
        }
        else
        {
            return ERR_INV_CMD;
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
            err_msg = functions(insts[i].value, operands, IC, DC, base64Chars, *label_lst, filename);
        }
        else
        {
            return ERR_INV_CMD;
        }
        break;
    case IS_COMMENT_EMPTY:
        break;
    }
    return err_msg;
}

void RunDecoder(FILE *SourceFile, char *fileName)
{
    FILE *objectFile;
    mem_word *label_lst;
    char line[MAX_LINE_LENGTH];
    int i, j, label_cnt;
    char **base64Chars;
    int err_msg, err_flag;
    int IC, DC;
    char IC_DC[30];
    char *label, *comd, *operands;
    char **lines;

    char ext_file[10];
    label_lst = malloc(10 * sizeof(mem_word));
    lines = malloc(10 * sizeof(line));
    base64Chars = (char **)malloc(3 * sizeof(char *));
    i = 0;
    IC = 0;
    DC = 0;
    err_flag = 0;
    label_cnt = 0;
    strtok(fileName, ".");
    strcpy(ext_file, fileName);
    fileName = strcat(fileName, ".ob");
    if ((objectFile = fopen(fileName, "w")) == NULL)
    {
        printf("Cannot open file %s\n", fileName);
        return;
    }

    rewind(SourceFile);
    j = 0;
    while (fgets(line, MAX_LINE_LENGTH, SourceFile) != NULL)
    {

        if (j > 10)
        {
            lines = realloc(lines, (j + 2) * sizeof(line));
        }
        lines[j] = malloc(sizeof(line));
        strcpy(lines[j], line);
        divider(line, &label, &comd, &operands);
        if (label_cnt > 10)
        {
            label_lst = realloc(label_lst, (label_cnt + 2) * sizeof(mem_word));
        }
        if (!strcmp(comd, ".extern"))
        {
            label_lst[label_cnt].name = (char *)malloc(strlen(operands) + 1);
            strcpy(label_lst[label_cnt].name, operands);
            label_lst[label_cnt].value = -1;
            label_cnt++;
            label_lst[label_cnt].value = 0;
        }

        if (label != NULL)
        {

            label_lst[label_cnt].name = (char *)malloc(strlen(label) + 1);
            strcpy(label_lst[label_cnt].name, label);
            label_lst[label_cnt].value = IC + DC + 100;
            label_cnt++;
            label_lst[label_cnt].value = 0;
        }
        decoder(line, j, &IC, &DC, &base64Chars, &label_lst, ext_file);

        j++;
    }

   
        delextFiles(ext_file);
    IC = 0;
    DC = 0;
    i = 0;
    while (i < j)
    {

        err_msg = decoder(lines[i], i, &IC, &DC, &base64Chars, &label_lst, ext_file);

        if (err_msg != -1)
        {
            err_flag = 1;
            printf("Error in line %d: %s\n", i + 1, error[err_msg].message);
        }
        i++;
    }

    if (!err_flag)
    {
        i = 0;
        sprintf(IC_DC, "%d %d\n", IC, DC);
        fputs(IC_DC, objectFile);

        while (i < IC + DC)
        {
            fputs(base64Chars[i], objectFile);
            fputs("\n", objectFile);
            i++;
        }
        printf("Done!\n");
    }
}
