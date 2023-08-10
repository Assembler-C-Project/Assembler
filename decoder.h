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

 

void decoder(char *line, int line_num, FILE *objectFile);
void RunDecoder(FILE *SourceFile, char *fileName);

#endif

