/*decoder.c
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: This code defines functions to decode assembly language lines, process labels and commands, and generate object files containing the base64 encoded instructions, IC, and DC values.*/
#include "decoder.h"

/* Define an array of command structures */
cmd cmds[] = {
    {"mov", MOV}, {"cmp", CMP}, {"add", ADD}, {"sub", SUB}, {"not", NOT}, {"clr", CLR}, {"lea", LEA}, {"inc", INC}, {"dec", DEC}, {"jmp", JMP}, {"bne", BNE}, {"red", RED}, {"prn", PRN}, {"jsr", JSR}, {"rts", RTS}, {"stop", STOP}
};

/* Define an array of instruction structures */
inst insts[] = {
    {".data", IS_DATA}, {".string", IS_STRING}, {".entry", IS_ENTRY}, {".extern", IS_EXTERN}
};

/* Main function for decoding a line */
int decoder(char *line, int line_num, int *IC, int *DC, char ***base64Chars, mem_word **label_lst, char *filename) {
    int i;
    char *label, *comd, *operands;
    int err_msg;
    int line_type;
    err_msg = -1;
    line_type = divider(line, &label, &comd, &operands);

    /* Check if label is valid */
    if (label != NULL && !is_valid_label(label)) {
        err_msg = ERR_INV_LABEL;
    }

    switch (line_type) {
    case IS_COMMAND:
        i = 0;
        /* Find the corresponding command in cmds array */
        while (i < 16) {
            if (!strcmp(comd, cmds[i].name)) {
                break;
            }
            i++;
        }
        if (i != 16) {
            /* Call the function associated with the command */
            err_msg = functions(cmds[i].value, operands, IC, DC, base64Chars, *label_lst, filename);
        } else {
            return ERR_INV_CMD;
        }
        break;
    case IS_INSTRUCTION:
        i = 0;
        /* Find the corresponding instruction in insts array */
        while (i < 4) {
            if (!strcmp(comd, insts[i].name)) {
                break;
            }
            i++;
        }
        if (i != 4) {
            /* Call the function associated with the instruction */
            err_msg = functions(insts[i].value, operands, IC, DC, base64Chars, *label_lst, filename);
        } else {
            return ERR_INV_CMD;
        }
        break;
    case IS_COMMENT_EMPTY:
        /* No need to process comments or empty lines */
        break;
    }
    return err_msg;
}

/* Function to run the decoder */
void RunDecoder(FILE *SourceFile, char *fileName) {
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

    /* Allocate memory for data structures */
    label_lst = malloc(10 * sizeof(mem_word));
    lines = malloc(10 * sizeof(line));
    base64Chars = (char **)malloc(3 * sizeof(char *));
    
    i = 0;
    IC = 0;
    DC = 0;
    err_flag = 0;
    label_cnt = 0;

    /* Tokenize the file name to remove extension */
    strtok(fileName, ".");
    strcpy(ext_file, fileName);
    fileName = strcat(fileName, ".ob");

    /* Open the output object file for writing */
    if ((objectFile = fopen(fileName, "w")) == NULL) {
        printf("Cannot open file %s\n", fileName);
        return;
    }

    /* Reset file pointer to the beginning of the source file */
    rewind(SourceFile);
    j = 0;

    /* Process each line in the source file */
    while (fgets(line, MAX_LINE_LENGTH, SourceFile) != NULL) {
        if (j > 10) {
            lines = realloc(lines, (j + 2) * sizeof(line));
        }
        lines[j] = malloc(sizeof(line));
        strcpy(lines[j], line);

        /* Extract label, command, and operands from the line */
        divider(line, &label, &comd, &operands);

        if (label_cnt > 10) {
            label_lst = realloc(label_lst, (label_cnt + 2) * sizeof(mem_word));
        }
        
        /* Process ".extern" commands and labels */
        if (comd != NULL && !strcmp(comd, ".extern")) {
            label_lst[label_cnt].name = (char *)malloc(strlen(operands) + 1);
            strcpy(label_lst[label_cnt].name, operands);
            label_lst[label_cnt].value = -1;
            label_cnt++;
            label_lst[label_cnt].value = 0;
        }

        if (label != NULL) {
            label_lst[label_cnt].name = (char *)malloc(strlen(label) + 1);
            strcpy(label_lst[label_cnt].name, label);
            label_lst[label_cnt].value = IC + DC + 100;
            label_cnt++;
            label_lst[label_cnt].value = 0;
        }

        /* Decode and process the line */
        decoder(line, j, &IC, &DC, &base64Chars, &label_lst, ext_file);
        j++;
    }

    /* Clean up external and entry files */
    delextFiles(ext_file);
    delentFiles(ext_file);

    /* Reset IC and DC for final pass */
    IC = 0;
    DC = 0;
    i = 0;

    /* Process each line again for final pass */
    while (i < j) {
        err_msg = decoder(lines[i], i, &IC, &DC, &base64Chars, &label_lst, ext_file);
        if (err_msg != -1) {
            err_flag = 1;
            printf("Error in line %d: %s\n", i + 1, error[err_msg].message);
        }
        i++;
    }

    /* Write the decoded data to the object file if no errors */
    if (!err_flag) {
        i = 0;
        sprintf(IC_DC, "%d %d\n", IC, DC);
        fputs(IC_DC, objectFile);

        while (i < IC + DC) {
            fputs(base64Chars[i], objectFile);
            fputs("\n", objectFile);
            i++;
        }
        printf("Done!\n");
    }
    else{
        delAllFiles(ext_file);
    }
}
