#ifndef DECODER_H
#define DECODER_H
#define MAX_LINE_LENGTH 80

#include "functions.h"
#include "Interpreter.h"

typedef struct cmd
{
    char *name;
    int value;
}cmd;

extern cmd cmds[16];

void decoder(char *line,int line_num);
void RunDecoder(FILE *SourceFile);

#endif
