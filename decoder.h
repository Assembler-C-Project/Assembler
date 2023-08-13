#ifndef DECODER_H
#define DECODER_H
#define MAX_LINE_LENGTH 80

#include "functions.h"
#include "Interpreter.h"


typedef struct cmd
{
    char *name;
    int value;
} cmd;

extern cmd cmds[16];

typedef struct inst

{
    char *name;
    int value;
} inst;
extern inst insts[4];

int decoder(char *line, int line_num, int *IC, int *DC, char ***base64Chars, mem_word **label_lst,char* filename);
void RunDecoder(FILE *SourceFile, char *fileName);

#endif
